# OSX route

## route batch mode, only support `add`, `delete` and `change`

```bash
sudo ./route -b <<EOF
  add -net 1.0.2.0/23 192.168.0.1
  add -net 1.0.1.0/24 192.168.0.1
EOF

sudo ./route -b <<EOF
  delete -net 1.0.2.0/23 192.168.0.1
  delete -net 1.0.1.0/24 192.168.0.1
EOF
```

or

```bash
sudo ./route -b routes.txt
```
