from bs4 import BeautifulSoup
import requests
import os
from urllib import request

class Subject:
    def __init__(self, name=None, lecturer=None, class_=None, time=None):
        self.name = name
        self.lecturer = lecturer
        self.class_ = class_
        self.time = time

def main():
    url = 'http://elektron.pol.lublin.pl/ats4/plan.php?type=0&id=6420&winW=943&winH=852&loadBG=000000'
    req = request.urlopen(url).read().decode('UTF-8')
    soup = BeautifulSoup(req, 'html.parser')
    #result = soup.find_all(id='course_6')
    result = soup.find_all('div', class_='coursediv')
    r2 = BeautifulSoup(str(result), 'html.parser')
    #print(r2.contents)
    #print(type(r2.text))
    #print(type(r2))
    #print(r2.text)
    tab = []
    for r in r2.contents:
        soup = BeautifulSoup(str(r), 'html.parser')
        #print(soup.text)
        if soup.text != ', ':
            tab.append(soup.text)
            subject = Subject()
            
        #print(type(soup.text))

    for s in tab:
        print(s)
    print(tab)

    data = ''
    file_path = os.path.join('.', 'data.txt')
    try:
        with open(file_path, 'w') as f:
            f.write(data)
    except FileNotFoundError:
        print('File not found!')


if __name__ == '__main__':
    main()
