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
        '<!@(pkg-config libusb-1.0 --cflags-only-I | sed s/-I//g)'
      ],
      'libraries': [
        '<!@(pkg-config libusb-1.0 --libs)'
      ]
    }
  ]
}
