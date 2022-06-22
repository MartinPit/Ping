#!/bin/sh

apt-get update
apt-get install mutt -y
apt-get install openssl -y
apt-get install libsasl2-2 -y
apt-get install gnutls-bin -y

if [ ! -d ~/.mutt ]; then
    mkdir ~/.mutt
fi

rm -rf ~/.mutt/muttrc

echo 'set imap_user = "mntrsrvc@gmail.com"
set imap_pass = "jeaypnmujojggjqw"
set smtp_url = "smtp://mntrsrvc@gmail.com@smtp.gmail.com:587/"
set smtp_pass = "jeaypnmujojggjqw"
set from = "mntrsrvc@gmail.com"
set realname = "Monitor Service"
set sendmail="/usr/bin/msmtp"

set header_cache =~/.mutt/cache/headers
set message_cachedir =~/.mutt/cache/bodies
set certificate_file =~/.mutt/certificates

set folder = "imaps://imap.gmail.com:993"
set spoolfile = "+INBOX"
set postponed = "+[Gmail]/Drafts"
set trash = "imaps://imap.gmail.com[Gmail]/Trash"' > ~/.mutt/muttrc

rm -rf ~/ping
mkdir ~/ping
cp ping.c ~/ping
out=`gcc -w ~/ping/ping.c -o ~/ping/ping 2>&1`

echo
echo "Vyrobila spoločnosť BySec s.r.o.. Všetky práva vyhradené 2022."