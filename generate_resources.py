#!/usr/bin/env python

import argparse
import json
import os.path

RESOURCE_MAP = 'resources/src/resource_map.json'
SOURCE_ROOT = 'src'

def generate_state(key):
  return "STATE_%s" % key.upper().replace('-', '_')

def generate_frame(file):
  return "FRAME_%s" % os.path.basename(file).replace('.png', '').replace('-', '_').upper()

def main():
  parser = argparse.ArgumentParser(description = "Generate resource and state machine structs for a JSON animation description.")
  parser.add_argument('description', help = 'Animation description file to process')
  parser.add_argument('project', help = 'Path to the project')
  options = parser.parse_args()

  project = os.path.abspath(options.project)
  resource_map = os.path.join(project, RESOURCE_MAP)
  resource_root = os.path.dirname(resource_map)
  description_root = os.path.dirname(options.description)
  source_root = os.path.join(project, SOURCE_ROOT)
  print resource_map

  # Read the description file.
  description = json.load(open(options.description))

  # Generate the state keys.
  states = []
  for key, value in description.iteritems():
    state = generate_state(key)
    states.append(state)

  # Generate the list of unique files.
  files_list = []
  for key, value in description.iteritems():
    for item in value['frames']:
      files_list.append(item['file'])

  # Generate the resource structure.
  media = []
  for file in set(files_list):

    # Check the file exists.
    abs_resource_path = os.path.abspath(os.path.join(description_root, file))
    rel_resource_path = os.path.relpath(abs_resource_path, resource_root)

    if not os.path.exists(abs_resource_path):
      print "File '%s' does not exist." % abs_resource_path
      exit(0)

    media.append({
      "type": "png",
      "defName": generate_frame(file),
      "file": rel_resource_path})

  resources = {
    'friendlyVersion': 'VERSION',
    'versionDefName': 'VERSION',
    'media': media}

  # Write the resource_map.
  with open(resource_map, 'w') as f:
    json.dump(resources, f, indent = 4) 

  # Write out the animation header.
  with open(os.path.join(source_root, 'animation.h'), 'w') as f:

    defines = []

    # Print the states.
    for index, key in enumerate(states):
      f.write('#define %s %d\n' % (key, index))

    f.write("""
struct animation {
  int length;
  int *frames;
  int *durations;
};

""")

    for key, value in description.iteritems():
      frames = []
      durations = []
      name_frames = "resource_frames_%s" % key.replace('-', '_')
      name_durations = "resource_durations_%s" % key.replace('-', '_')
      name = "resource_%s" % key.replace('-', '_')
      for item in value['frames']:
        file = item['file'] # Path to file.
        id = "RESOURCE_ID_%s" % generate_frame(file)
        frames.append(id)
        duration = item['duration'] * 1000 # Duration in milliseconds
        durations.append(str(int(duration)))
      f.write("int %s[%d] = { %s };\n" % (name_frames, len(frames), ", ".join(frames)))
      f.write("int %s[%d] = { %s };\n" % (name_durations, len(durations), ", ".join(durations)))
      f.write("struct animation %s = { %d, %s, %s };\n" % (name, len(frames), name_frames, name_durations))
      f.write("\n")


  #print json.dumps(resources)

# {"friendlyVersion": "VERSION",
#  "versionDefName": "VERSION",
#  "media": [
#      {
#       "type":"png",
#       "defName":"FRAME_BLINK_01",
#       "file":"images/blink-01.png"
#      },
#      {
#       "type":"png",
#       "defName":"FRAME_BLINK_02",
#       "file":"images/blink-02.png"
#      },
#      {
#       "type":"png",
#       "defName":"FRAME_BLINK_03",
#       "file":"images/blink-03.png"
#      }
#     ]
# }



if __name__ == '__main__':
  main();


