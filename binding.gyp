{
  'targets': [
    {
      'target_name': 'bindings',
      'cflags_cc!': [
        '-fno-exceptions'
      ],
      'sources': [
        'binding.cc',
      ],
      'include_dirs+': [
        "<!@(node -p \"require('node-addon-api').include\")",
      ]
    }
  ]
}
