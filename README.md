# HOW TO USE
## config file
Please refer the '.ssh-manager' directory and make it on your home directory.
You can make multiple config file

### Example of config file (~/.ssh-manager.conf/.ssh-manager.conf.A)
alias field should be filled, eventhough it is empty.
```
[
    {
        "username": "travis",
        "ip": [
            {"address": "192.168.45.131", "alias": "miniPC"},
            {"address": "192.168.45.132", "alias": "unknown"}
        ]
    },
    {
        "username": "chanhoo",
        "ip": [
            {"address": "192.168.131", "alias": "wrongPC"},
            {"address": "192.168.132", "alias": "foo"}
        ]
    }
]
```
