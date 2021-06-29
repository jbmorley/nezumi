#!/usr/bin/env python

import argparse
import subprocess

def pebble(args):
   command = ["pebble"]
   subprocess.check_call(command + args)   

def main():
   parser = argparse.ArgumentParser(description = "Compile the Nezumi Pebble watch app.")
   parser.add_argument("--install", help = "Install the watch app")
   options = parser.parse_args()

   subprocess.check_call(["tools/addimages",
                          "resources/images/",
                          "appinfo-template.json",
                          "."])
   subprocess.check_call(["tools/makestruct",
                          "json/types.json",
                          "json/data.json",
                          "src/animation.h"])
   
   pebble(["clean"])
   pebble(["build"])

   if options.install:
      pebble(["install", "--phone", options.install])
   
if __name__ == "__main__":
   main()
