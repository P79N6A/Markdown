import urllib

proxies = {'http': 'http://qflow.proxy.oa.com'}
fd = urllib.urlopen("http://work.idc.sng.local/release/cgi-bin/test/hello.py", proxies=proxies)
# Don't use any proxies
#fd = urllib.urlopen("http://qflow.oa.com/cgi-bin/hello.py", proxies={})

print fd.read()
