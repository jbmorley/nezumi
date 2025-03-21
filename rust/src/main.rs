use serde::Deserialize;
use std::collections::HashMap;
use std::fs;
use raylib::prelude::*;

const SCALE: f32 = 3.0;
const WINDOW_WIDTH: i32 = 360;
const WINDOW_HEIGHT: i32 = 360;

#[derive(Debug, Deserialize)]
struct Frame {
    // TODO: Rename to file_name?
    file: String,
    duration: f64,
}

#[derive(Debug, Deserialize)]
struct Operation {
    set: String,
}

#[derive(Debug, Deserialize)]
struct State {
    frames: Vec<Frame>,
    actions: HashMap<String, Operation>,
}

type FrameMap = HashMap<String, raylib::core::texture::Texture2D>;

fn main() {
    println!("Hello, world!");

    // Standard frame size seems to be 90 x 90.

    let contents = fs::read_to_string("states.json")
        .expect("Unable to read animation data");
    println!("{}", contents);

    let state: HashMap<String, State> = serde_json::from_str(&contents)
        .expect("Invalid animation data");

    let (mut rl, thread) = raylib::init()
        .size(WINDOW_WIDTH, WINDOW_HEIGHT)
        .title("Nezumi")
        .build();

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

    let frame_duration = 0.3;
    
    let mut frame = 0;
    let mut accumulator = 0.0;
    let mut current_state_name = "blink";
    let mut action = "default";  // TODO: Unnecessary?

    while !rl.window_should_close() {
        let mut current_state = &state[current_state_name];
        let frame_count = current_state.frames.len();

        // Handle gestures.
        let current_gesture = rl.get_gesture_detected();
        if current_gesture == raylib::consts::Gesture::GESTURE_DRAG {
            action = "drag";
        } else if current_gesture == raylib::consts::Gesture::GESTURE_TAP {
            action = "tap";
        } else if current_gesture == raylib::consts::Gesture::GESTURE_HOLD {
            // Ideally a hold gesture would clear the effect of the tap, but
            // Raylib always seems to give us a 'hold' after a tap, so we can't
            // easily differentiate between these two states.
            action = "tap";
        } else {
            // action = "default";
        }

        accumulator += rl.get_frame_time();
        while accumulator > frame_duration {
            accumulator -= frame_duration;
            frame += 1;

            // Handle state transitions if we've reached the end of the
            // current animation loop.
            if frame >= frame_count {
                frame = 0;
                current_state_name = &current_state.actions[action].set;
                current_state = &state[current_state_name];

                // Reset the action.
                action = "default";
            }
        }

        let frame_name = &current_state.frames[frame].file;

        let mut d = rl.begin_drawing(&thread);
        d.clear_background(Color::WHITE);

        let texture = &frames[frame_name];
        d.draw_texture_ex(
            texture,
            Vector2 {x: 0.0, y: 0.0},
            0.0,
            SCALE,
            Color::WHITE);
        
    }
}
