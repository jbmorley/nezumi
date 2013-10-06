#!/usr/bin/env python

import argparse
import json
import os.path

RESOURCE_MAP = 'resources/src/resource_map.json'

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
  print resource_map

  # Read the description file.
  description = json.load(open(options.description))

  # Generate the state keys.
  states = []
  for key, value in description.iteritems():
    state = generate_state(key)
    states.append(state)

  # Print the states.
  # for index, key in enumerate(states):
  #   print '#define %s %d' % (key, index)

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
    print abs_resource_path
    print rel_resource_path

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


