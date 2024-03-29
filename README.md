# PING

Ping is a C CLI program that continously checks the provided IPs and sends an info email
when any of the IPs fails to respond.

## Installation

Use the provided install.sh script to install and prepare the enviroment.

```bash
$ sudo sh install.sh
```

## Usage

Change the directory into the install folder

```bash
$ cd ~/ping
```

Start the application in the foreground and give it up to 5 IPs, close it using the key combo of Ctrl+C

```bash
$ ./ping 1.1.1.1 2.2.2.2 ...
```

Start the application in the background by using & at the end of the command and give it up to 5 IPs

```bash
$ ./ping 1.1.1.1 2.2.2.2 ... &
$ [1] 7972
```

After starting the application in the background you can stop it using the kill command and the given PID (see above)

```bash
$ kill 7972
```

![MartinPit's GitHub stats](https://github-readme-stats.vercel.app/api?username=martinpit&count_private=true&show_icons=True&bg_color=1e1e2e&text_color=cdd6f4&icon_color=cba6f7&title_color=94e2d5)
