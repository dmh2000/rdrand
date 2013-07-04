{
  "targets": [
    {
      "target_name": "irand",
      "conditions": [
        ["OS=='win'",
          {
            "sources": [
              "irand.cpp",
              "w/ia_rdrand.c",
              "w/rdrand64.obj",
            ]
          }
        ],
        ["OS!='win'",
          {
            "sources": [
              "irand.cpp",
              "u/rdrand.c",
            ]
          }
        ]
      ]
  }
  ]
}

