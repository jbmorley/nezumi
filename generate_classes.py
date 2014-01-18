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
      return "struct %s * %s" % (self.type, self.name)
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

      # We automatically create the array types.
      # This magically works because the type will be added before we have
      # been created, ensuring that it is defined in advance of ourselves.
      if (type.find("__array__") == 0):
        if not self.types.defined(type):
          self.types.add(Type(self.types, { "__name__": type, "length": "int", "items": "struct %s **" % type[9:] }))

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

    self.type = "__array__%s" % self.item_type()


  def item_type(self):

    # Determine the types of the items.
    array_type = None
    for item in self.items:
      if (array_type != None and array_type != item.type()):
        raise Exception("Mixed types in array")
      array_type = item.type()

    return array_type

  def __repr__(self):

    items_name = '%s_items' % self.name

    # We currently only support arrays of structs, so it is
    # acceptable to assume struct contents.

    items = "\n".join(map(lambda x: str(x), self.items))
    names = ", ".join(map(lambda x: "&%s" % x.name, self.items))
    array = "struct %s * %s[%d] = { %s }" % (self.item_type(), items_name, len(self.items), names)
    # return "%s\n%s;\n%s" % (items, array, instance)
    # count = "int %s_length = %d;" % (self.name, len(self.items))
    item = "struct %s %s = { %d, %s_items };" % (self.type, self.name, len(self.items), self.name )
    return "%s\n%s;\n%s" % (items, array, item)


class Property:

  # TODO We need to know what type we are!
  # This must be inferred from our superclass?
  def __init__(self, types, name, value, type):
    self.types = types
    self.name = name
    self.value = value
    self.type = type

  def __repr__(self):
    return "%s %s = %s;" % (self.type, self.name, str(self.value))


class Instance():

  def __init__(self, types, name, structure):
    self.types = types
    self.name = name
    self.structure = structure
    self.t = self.structure['__type__']

    self.structure.pop('__type__', None)

    # Instantiate our sub-structures.
    self.fields = {}
    for name, details in self.structure.iteritems():
      field = self.types.type(self.type()).field(name)
      self.fields[name] = create_instance(self.types, "%s_%s" % (self.name, name), details, field.type)

  def type(self):
    return self.t

  def __repr__(self):
    fields = "\n".join(map(lambda x: str(self.fields[x.name]), self.types.type(self.type()).fields))

    field_names = []
    for field in self.types.type(self.type()).fields:
      instance = self.fields[field.name];
      if self.types.defined(instance.type):
        field_names.append("&%s" % instance.name)
      else:
        field_names.append(str(instance.value))

    struct = "struct %s %s = { %s }" % ( self.type(), self.name, ", ".join(field_names) )
    return "%s\n%s;" % (fields, struct)


def create_instance(types, name, structure, type = None):

  if isinstance(structure, dict):
    return Instance(types, name, structure)
  elif isinstance(structure, list):
    return Array(types, name, structure)
  else:
    return Property(types, name, structure, type)

class Data:

  def __init__(self, types, structure):
    self.types = types
    self.structure = structure
    self.items = []
  
    for name, definition in structure.iteritems():
      self.items.append(create_instance(self.types, name, definition))

  def __repr__(self):
    return "\n".join(map(lambda x: str(x), self.items))



def main():
  parser = argparse.ArgumentParser(description = "Generate resource and state machine structs for a JSON animation description.")
  parser.add_argument('classes', help = 'Class definitions')
  parser.add_argument('data', help = 'Data')
  options = parser.parse_args()

  structure = json.load(open(options.data))
  
  # Create the types.
  types = Types(json.load(open(options.classes)))

  # Create the data.
  data = Data(types, json.load(open(options.data)))

  print types
  print data

  exit()

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
