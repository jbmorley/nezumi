#!/usr/bin/env python

import json
import argparse

class TypeField:

  def __init__(self, types, name, type):
    self.types = types
    self.name = name
    self.type = type

  def __repr__(self):

    # Check to see if we are a special kind of type (aka a struct defined
    # within our types.
    if self.types.defined(self.type):
      return "struct %s %s" % (self.type, self.name)
    else:
      return "%s %s" % (self.type, self.name)


class Type:

  def __init__(self, types, structure):
    self.types = types
    self.structure = structure
    self.name = self.structure["__name__"]
    self.fields = []
    self.lookup = {}

    # Remove the name from the dictionary.
    self.structure.pop('__name__', None)

    # Iterate over the types generating the fields.
    for name, type in self.structure.iteritems():
      t = TypeField(self.types, name, type)
      self.fields.append(t)
      self.lookup[name] = t

  def field(self, name):
    return self.lookup[name]

  def __repr__(self):
    return "struct %s {\n  %s;\n};\n" % (self.name, ";\n  ".join(map(lambda x: str(x), self.fields)));


class Types:

  def __init__(self, structure):
    self.structure = structure
    self.items = []
    self.lookup = {}

    for item in self.structure:
      self.add(Type(self, item))

  def add(self, type):
    if not type.name in self.lookup:
      self.items.append(type)
      self.lookup[type.name] = type

  def names(self):
    return ['bob']

  def type(self, name):
    return self.lookup[name]

  def defined(self, name):
    return name in self.lookup

  def __repr__(self):
    return "\n".join(map(lambda x: str(x), self.items))


class Array():

  def __init__(self, types, name, structure):
    self.types = types
    self.name = name
    self.structure = structure

    # Populate the contents.
    self.items = []
    for index, item in enumerate(self.structure):
      self.items.append(create_instance(self.types, "%s_item_%d" % (self.name, index), item))

    # Create a type for ourselves.
    item_type = self.item_type()
    type = self.type()
    self.types[type] = Class(self.types, type, { "length": "int", "items": "%s *" % item_type })


  def item_type(self):

    # Determine the types of the items.
    array_type = None
    for item in self.items:
      if (array_type != None and array_type != item.type()):
        raise Exception("Mixed types in array")
      array_type = item.type()

    return array_type

  def type(self):
    return "%sArray" % self.item_type()


  def __repr__(self):

    items_name = '%s_items' % self.name

    instance = str(Instance(self.types, self.name, { 'type': self.type(), 'items': items_name, 'length': len(self.items) }))
    items = "\n".join(map(lambda x: str(x), self.items))
    names = ", ".join(map(lambda x: x.name, self.items))
    array = "%s %s[%d] = { %s }" % (self.item_type(), items_name, len(self.items), names)
    return "%s\n%s\n%s\n\n" % (items, array, instance)


class Property:

  # TODO We need to know what type we are!
  # This must be inferred from our superclass?
  def __init__(self, types, name, value, type):
    self.types = types
    self.name = name
    self.value = value
    self.type = type

  def __repr__(self):
    #return "%s %s = %s" % (self.type, self.name, str(self.value))
    return "#define %s %s" % (self.name, str(self.value))


class Instance():

  def __init__(self, types, name, structure):
    self.types = types
    self.name = name
    self.structure = structure
    self.t = self.structure['type']

    self.structure.pop('type', None)

    # Instantiate our sub-structures.
    self.fields = {}
    for name, details in self.structure.iteritems():
      field = self.types[self.type()].field(name)
      self.fields[name] = create_instance(self.types, "%s_%s" % (self.name, name), details, field.type)


  def type(self):
    return self.t

  def __repr__(self):

    # TODO Instantiate our sub-structures?
    fields = "\n".join(map(lambda x: str(self.fields[x.name]), self.types[self.type()].fields))
    field_names = ", ".join(map(lambda x: str(self.fields[x.name].name), self.types[self.type()].fields))
    struct = "struct %s %s = { %s }" % ( self.type(), self.name, field_names )
    return "%s\n%s;" % (fields, struct)


def create_instance(types, name, structure, type = None):

  if isinstance(structure, dict):
    return Instance(types, name, structure)
  elif isinstance(structure, list):
    return Array(types, name, structure)
  else:
    return Property(types, name, structure, type)


def main():
  parser = argparse.ArgumentParser(description = "Generate resource and state machine structs for a JSON animation description.")
  parser.add_argument('classes', help = 'Class definitions')
  parser.add_argument('structure', help = 'Structure')
  options = parser.parse_args()

  classes = json.load(open(options.classes))
  structure = json.load(open(options.structure))
  
  # Create the types.
  types = Types(json.load(open(options.classes)))
  print types
  exit()

  # Create the types.
  types = {}
  for name, c in classes.iteritems():
    types[name] = Class(types, name, c)

  # Internalise the items.
  items = []
  for name, definition in structure.iteritems():
    items.append(create_instance(types, name, definition))

  # Print the types.
  for name, type in types.iteritems():
    print types[name]

  # Print the items.
  for item in items:
    print str(item)

if __name__ == '__main__':
  main();
