# HOW TO USE
This program is made for connecting/managing to multiple hosts easily.
You can access to the other hosts and send/receive the files to/from the other hosts easily.
For using this, `ssh` and `scp` must be installed in your systems. 

## config file
Please refer the '.ssh-manager' directory and make it on your home directory.
You can make multiple config file
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

## Execute the binary
```
travis@DESKTOP-TVCKN81:~/project/toy/ssh-manager$ ./ssh-manager

0 : /home/travis/.ssh-manager.conf/ssh-manager.conf.A
1 : /home/travis/.ssh-manager.conf/ssh-manager.conf.B
------------------------------------------------
Select the target config file : 0

0 : travis@192.168.45.131 (miniPC)
1 : travis@192.168.45.132 ()
2 : chanhoo@192.168.131 (wrongPC)
3 : chanhoo@192.168.132 (foo)
------------------------------------------------
Select the target server : 0
Trying to connect to travis@192.168.45.131
ssh -X travis@192.168.45.131
travis@192.168.45.131's password:
```
