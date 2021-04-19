#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
#   This is python sample
#   hidekuno@gmail.com
import sys 
import argparse
import urllib.request
import nntplib
import traceback
from html.parser import HTMLParser

def gmane():
    s = nntplib.NNTP('news.gmane.io')
    for n in s.list()[1]:
        print(n.group)
    s.quit()

def fj():
    class MyHTMLParser(HTMLParser):
        def handle_starttag(self, tag, attrs):
            if len(attrs) > 0 and attrs[0][1][:5] == "news:":
                print(attrs[0][1][5:])

    u = urllib.request.urlopen('http://www.fj-news.org/active/fj-active-2006-07-20.html.en')
    b = u.read()
    u.close()
    parser = MyHTMLParser()
    parser.feed(b.decode('utf-8'))

try:
    parser = argparse.ArgumentParser()
    parser.add_argument('-f','--fj',  action='store_true')
    parser.add_argument('-g','--gmane',  action='store_true')
    args = parser.parse_args(sys.argv[1:])

    if args.fj:
        fj()
    elif args.gmane:
        gmane()
    else:
        fj()

except Exception as e:
    print(e, traceback.format_exc(), file=sys.stderr)
    sys.exit(1)
