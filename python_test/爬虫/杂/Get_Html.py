import requests

def getHTML(url):
    try:
        headers = {
            'User-Agent': 'User-Agent:Mozilla/5.0 (Macintosh; Intel Mac OS X 10_12_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'}
        r = requests.get(url,headers =headers ,timeout = 10)
        r.raise_for_status()
        r.encoding =r.apparent_encoding
        return r.text
    except:
        print("错误")