# HOW TO USE
This program is made for connecting/managing to multiple hosts easily.  
You can access to the other hosts and send/receive the files to/from the other hosts easily.  
For using this, `ssh` and `scp` must be installed in your systems.  

## config file
Please refer the '.ssh-manager.conf' directory and make it on your home directory(copy it).  
You can also make multiple config file  
```
git clone <...>
cd ssh-manager
cp -rfp .ssh-manager.conf ~/
```

### Example of config file (~/.ssh-manager.conf/.ssh-manager.conf.A)
alias field should be filled, eventhough it is empty. (Format as json)  
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
            {"address": "192.168.131", "alias": ""},
            {"address": "192.168.132", "alias": "foo"}
        ]
    }
]
```
