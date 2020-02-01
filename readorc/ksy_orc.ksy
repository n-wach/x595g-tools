meta:
  id: ksy_orc
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
  word28:
    seq:
      - id: unpacked
        type: u4
    instances:
      v:
        value: ((unpacked & (0b11111111 << 0)) << 0) |
               ((unpacked & (0b11111111 << 8)) >> 1) |
               ((unpacked & (0b11111111 << 16)) >> 2) |
               ((unpacked & (0b11111111 << 24)) >> 3)

  symbol_table:
    seq:
      - id: num_entries
        type: word28
      - id: symbols
        type: symbol
        repeat: expr
        repeat-expr: num_entries.v
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
        type: word28
        if: is_defined == bool::true
      - id: offset
        type: word28
        if: is_defined == bool::true
  relocation_table:
    seq:
      - id: num_entries
        type: word28
      - id: relocations
        type: relocation
        repeat: expr
        repeat-expr: num_entries.v
  relocation:
    seq:
      - id: offset
        type: word28
      - id: section
        type: word28
      - id: symbol
        type: strz
        encoding: ascii
      - id: plus
        type: word28
  section_table:
    seq:
      - id: num_entries
        type: word28
      - id: sections
        type: section
        repeat: expr
        repeat-expr: num_entries.v
  section:
    seq:
      - id: permissions
        type: u1
      - id: offset
        type: word28
      - id: name
        type: strz
        encoding: ascii
      - id: size
        type: word28
  segment_table:
    seq:
      - id: num_entries
        type: word28
      - id: segments
        type: segment
        repeat: expr
        repeat-expr: num_entries.v
  segment:
    seq:
      - id: name
        type: strz
        encoding: ascii
      - id: offset
        type: word28
      - id: base
        type: word28
      - id: permissions
        type: word28
      - id: type
        type: u1
        enum: segment_type



