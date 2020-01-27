meta:
  id: orc
  file-extension: orc
  endian: le

enums:
  file_type:
    0: exe
    1: obj
  bool:
    0: false
    1: true
  segment_type:
    2: progbits
    1: note

seq:
  - id: header
    contents: ['orc', 0]
  - id: file_type
    type: u1
    enum: file_type

  - id: has_entry_point
    type: u1
    enum: bool

  - id: entry_point
    type: u1
    if: has_entry_point == bool::true

  - id: symbol_table
    type: symbol_table

  - id: relocation_table
    type: relocation_table

  - id: section_table
    type: section_table

  - id: segment_table
    type: segment_table


  - id: contents
    type: u1
    repeat: eos

types:
  symbol_table:
    seq:
      - id: num_entries
        type: u4
      - id: symbols
        type: symbol
        repeat: expr
        repeat-expr: num_entries
  symbol:
    seq:
      - id: name
        type: str
        terminator: 0
        encoding: ascii
      - id: is_defined
        type: u1
        enum: bool
      - id: section
        type: u4
        if: is_defined == bool::true
      - id: offset
        type: u4
        if: is_defined == bool::true
  relocation_table:
    seq:
      - id: num_entries
        type: u4
      - id: relocations
        type: relocation
        repeat: expr
        repeat-expr: num_entries
  relocation:
    seq:
      - id: offset
        type: u4
      - id: section
        type: u4
      - id: symbol
        type: strz
        encoding: ascii
      - id: plus
        type: u4
  section_table:
    seq:
      - id: num_entries
        type: u4
      - id: sections
        type: section
        repeat: expr
        repeat-expr: num_entries
  section:
    seq:
      - id: permissions
        type: u1
      - id: offset
        type: u4
      - id: name
        type: strz
        encoding: ascii
      - id: size
        type: u4
  segment_table:
    seq:
      - id: num_entries
        type: u4
      - id: segments
        type: segment
        repeat: expr
        repeat-expr: num_entries
  segment:
    seq:
      - id: name
        type: strz
        encoding: ascii
      - id: offset
        type: u4
      - id: base
        type: u4
      - id: permissions
        type: u1
      - id: type
        type: u1
        enum: segment_type


