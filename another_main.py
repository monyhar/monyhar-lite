(lambda req, url: req.urlopen(req.Request(url, headers={'User-Agent': 'monyhar/0.0.2'})).read())(__import__('urllib.request').request, input('请输入网址：'))
#
