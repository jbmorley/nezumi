use serde::Deserialize;
use std::collections::{HashMap, HashSet};
use std::fs;
use raylib::prelude::*;
use rand::Rng;

use std::sync::{
    atomic::{AtomicBool, Ordering},
    Arc,
};

const APP_NAME: &str = "Nezumi";

const DEFAULT_WINDOW_WIDTH: i32 = 360;
const DEFAULT_WINDOW_HEIGHT: i32 = 360;

const TAP_GESTURE_MINIMUM_DISTANCE: f32 = 0.1;  // Given as a fraction of the window size.

const DEFAULT_FRAME_DURATION: f32 = 3.0;

const FULL_ENERGY: i32 = 10;
const START_STATE: &str = "splash";

#[derive(Debug, Deserialize)]
struct Frame {
    file: String,
    duration: f32,
}

#[derive(Debug, Deserialize)]
struct State {
    frames: Vec<Frame>,
    next_state: String,
    actions: Vec<Transition>,
    side_effects: HashSet<SideEffect>
}

#[derive(Debug, Deserialize)]
struct Transition {
    event: Event,
    state: String,
}

#[derive(Debug, Deserialize, PartialEq, Eq, Hash)]
#[serde(rename_all = "snake_case")]
enum SideEffect {
    IncrementEnergy,
    DecrementEnergy,
    DecrementEnergyHigh,
}

type FrameMap = HashMap<String, raylib::core::texture::Texture2D>;

#[derive(Debug, Deserialize, PartialEq, Eq, Hash, Clone)]
#[serde(rename_all = "snake_case")]
enum Event {
    Drag,
    Tap,

    HighEnergy,
    LowEnergy,

    StateAgeExceedsShortRandom,
    StateAgeExceedsLongRandom,
}

// Random after timeout?
// StateAgeExceedsShortRandom---the time spent in the current state exceeds a random time between 5-10s.
// StateAgeExceedsLongRandom

// TODO: Consider requiring transitions for all events to avoid trapped states.
// TODO: Perhaps evaluation of the events results in a code evaluation which would allow for them not to
//       be pure events? Maybe conditions?
// We can capture state about the current scenario and inject it?

#[derive(Debug)]
enum Gesture {
    TAP,
    DRAG,
    NONE,
}

#[derive(Debug)]
struct CharacterState {
    energy: i32,
}

impl CharacterState {

    fn is_high_energy(&self) -> bool {
        self.energy >= FULL_ENERGY
    }

    fn is_low_energy(&self) -> bool {
        self.energy <= 0
    }

    fn increment_energy(&mut self) {
        self.energy = self.energy + 1;
    }

    fn decrement_energy(&mut self, value: i32) {
        self.energy = self.energy - value;
    }

}

#[derive(Debug)]
struct StateState<'a> {
    name: &'a str,
    age: f32
}

fn evaluate_event(event: &Event, character_state: &CharacterState, state_state: &StateState, events: &HashSet<Event>) -> bool {
    match event {
        Event::Tap => {
            events.contains(&Event::Tap)  // TODO: Clean up event model.
        },
        Event::Drag => {
            events.contains(&Event::Drag)  // TODO: Clean up event model.
        },
        Event::HighEnergy => {
            character_state.is_high_energy()
        },
        Event::LowEnergy => {
            character_state.is_low_energy()
        },
        Event::StateAgeExceedsShortRandom => {
            let mut rng = rand::rng();
            state_state.age >= rng.random_range(0.5..4.0)
        },
        Event::StateAgeExceedsLongRandom => {
            let mut rng = rand::rng();
            state_state.age >= rng.random_range(20.0..30.0)
        }
    }
}

fn main() {

    // Set up an atomic boolean to respond to Ctrl + C signals.
    let running = Arc::new(AtomicBool::new(true));
    let r = running.clone();
    ctrlc::set_handler(move || {
        r.store(false, Ordering::SeqCst);
    })
    .expect("Failed to set cancellation handler.");

    let contents = fs::read_to_string("states.json")
        .expect("Unable to read animation data");
    println!("{}", contents);

    let state: HashMap<String, State> = serde_json::from_str(&contents)
        .expect("Invalid animation data");

    let (mut rl, thread) = if cfg!(feature = "drm") {
        let width = unsafe { raylib::ffi::GetMonitorWidth(0) };
        let height = unsafe { raylib::ffi::GetMonitorHeight(0) };
        raylib::init()
            .size(width, height)
            .title(&APP_NAME)
            .resizable()
            .fullscreen()
            .build()
    } else {
        raylib::init()
            .size(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT)
            .title(&APP_NAME)
            .resizable()
            .build()
    };

    rl.set_target_fps(60);

    let mut frames: FrameMap = FrameMap::new();

    // Cache all the frames.
    let paths = fs::read_dir("frames")
        .expect("Failed to list frames");
    for path in paths {
        let a = path.unwrap().path();
        let b = a.to_str().unwrap();
        let image = Image::load_image(&b)
            .expect("Failed to load image");
        let texture = rl.load_texture_from_image(&thread, &image)
            .expect("Failed to create texture");
        frames.insert(a.file_name().unwrap().to_str().unwrap().to_owned(), texture);
    }

    let mut gesture = Gesture::NONE;
    let mut last_position = Vector2::new(0.0, 0.0);

    let mut frame_duration = DEFAULT_FRAME_DURATION;
    let mut frame = 0;
    let mut accumulator = 0.0;

    let mut state_state = StateState { name: START_STATE, age: 0.0 };

    let mut events = HashSet::<Event>::new();

    let mut character_state = CharacterState { energy: FULL_ENERGY };

    while !rl.window_should_close() && running.load(Ordering::SeqCst) {

        // Get the screen / window size.
        let window_width = rl.get_screen_width();
        let window_height = rl.get_screen_height();

        // Determine the current gesture.
        if rl.is_mouse_button_pressed(MouseButton::MOUSE_BUTTON_LEFT) {
            gesture = Gesture::TAP;
            last_position = rl.get_mouse_position();
        }
        if rl.is_mouse_button_down(MouseButton::MOUSE_BUTTON_LEFT) && last_position.distance_to(rl.get_mouse_position()) > (window_width as f32 * TAP_GESTURE_MINIMUM_DISTANCE) {
            gesture = Gesture::DRAG;
        }
        if rl.is_mouse_button_released(MouseButton::MOUSE_BUTTON_LEFT) {
            gesture = Gesture::NONE;
        }

        let mut current_state = &state[state_state.name];
        let frame_count = current_state.frames.len();

        // Convert gestues into events.
        match gesture {
            Gesture::TAP => {
                events.insert(Event::Tap);
            },
            Gesture::DRAG => {
                events.remove(&Event::Tap);
                events.insert(Event::Drag);
            },
            Gesture::NONE => {
                events.remove(&Event::Drag);
            },
            _ => {}
        }

        let frame_time = rl.get_frame_time();
        accumulator += frame_time;
        state_state.age += frame_time;
        while accumulator > frame_duration {
            accumulator -= frame_duration;
            frame += 1;

            if frame < frame_count {
                continue;
            }

            // Perform side effects.
            for side_effect in &current_state.side_effects {
                println!("{:?}", side_effect);
                match side_effect {
                    SideEffect::IncrementEnergy => {
                        character_state.increment_energy();
                    },
                    SideEffect::DecrementEnergy => {
                        character_state.decrement_energy(1);
                    },
                    SideEffect::DecrementEnergyHigh => {
                        character_state.decrement_energy(2);
                    }
                }
            }

            // Print the current state.
            println!(
                "character_state = {:?}, state_state = {:?}, events = {:?}",
                character_state,
                state_state,
                events
            );

            // Determine the next state.
            // Select the next state and then override with event-based transitions.
            let mut next_state_name = &current_state.next_state;
            for transition in &current_state.actions {
                if !evaluate_event(&transition.event, &character_state, &state_state, &events) {
                    continue;
                }
                events.remove(&transition.event);
                next_state_name = &transition.state;
                println!("{:?} -> {}", transition.event, next_state_name);
            }

            // Reset the frame.
            frame = 0;

            // Update the state and reset the state state if it we've changed state.
            if state_state.name != next_state_name {
                state_state = StateState { name: &next_state_name, age: 0.0 };
                current_state = &state[state_state.name];
            }

        }

        // Get the frame and details.
        let frame = &current_state.frames[frame];
        let texture = &frames[&frame.file];
        frame_duration = frame.duration;

        // Scale and center the image.
        let target_size = 0.8 * std::cmp::min(window_width, window_height) as f32;
        let target_scale = std::cmp::max((target_size / texture.width as f32).floor() as i32, 1) as f32;  // Assume textures are square.
        let frame_width = texture.width as f32 * target_scale;
        let frame_height = texture.height as f32 * target_scale;

        // Draw the current frame.
        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::new(214, 234, 248, 255));
        d.draw_texture_ex(
            texture,
            Vector2 {
                x: ((window_width as f32 - frame_width) / 2.0).floor(),
                y: ((window_height as f32 - frame_height) / 2.0).floor()
            },
            0.0,
            target_scale,
            Color::WHITE
        );

    }

}
