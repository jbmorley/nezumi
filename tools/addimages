#!/usr/bin/env python

import argparse
import json
import os.path

RESOURCE_MAP = 'appinfo.json'
SOURCE_ROOT = 'src'

def generate_frame(file):
  return "%s" % os.path.basename(file).replace('.png', '').replace('-', '_').upper()


def main():
  parser = argparse.ArgumentParser(description = "Generate resource and state machine structs for a JSON animation description.")
  parser.add_argument('directory', help = 'Directory containing the resources')
  parser.add_argument('template', help = 'Template appinfo.json')
  parser.add_argument('project', help = 'Path to the project')
  options = parser.parse_args()

  project = os.path.abspath(options.project)
  resource_map = os.path.join(project, RESOURCE_MAP)
  resource_root = os.path.join(project, 'resources')

  # Read the template.
  template = json.load(open(options.template));

  # Generate the list of files in the directory.
  files = [ os.path.join(options.directory, f) for f in os.listdir(options.directory) if os.path.isfile(os.path.join(options.directory, f)) ]

  # Generate the resource structure.
  media = []
  for file in set(files):

    # Check the file exists.
    abs_resource_path = os.path.abspath(file)
    rel_resource_path = os.path.relpath(abs_resource_path, resource_root)

    if not os.path.exists(abs_resource_path):
      print "File '%s' does not exist." % abs_resource_path
      exit(0)

    media.append({
      "type": "png",
      "name": generate_frame(file),
      "file": rel_resource_path})

  resources = {'media': media}

  # Write the contents into the template.
  template['resources'] = resources

  # Write the resource_map.
  with open(resource_map, 'w') as f:
    json.dump(template, f, indent = 2)



if __name__ == '__main__':
  main();


