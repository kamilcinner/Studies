from bs4 import BeautifulSoup
import requests

def main():
    response = requests.get("http://docs.gl/")

    html_doc = response.text

    soup = BeautifulSoup(html_doc, 'html.parser')

    result = soup.find_all("a", href=True)

    for r in result:
        #print(r)
        print(f"{r.get('href')} - {r.string}")


if __name__ == "__main__":
    main()
