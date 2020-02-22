from bs4 import BeautifulSoup
import requests


def main():
    response = requests.get("https://www.filmweb.pl/film/Narodziny+gwiazdy-2018-542576")

    html_doc = response.text

    soup = BeautifulSoup(html_doc, 'html.parser')

    director = soup.find(itemprop="director")
    director_soup = BeautifulSoup(str(director), 'html.parser')
    director_name = director_soup.find(itemprop="name")
    director_name_soup = BeautifulSoup(str(director_name), 'html.parser')

    release_date = soup.find(href="/film/Narodziny+gwiazdy-2018-542576/dates")
    release_date_soup = BeautifulSoup(str(release_date), 'html.parser')
    release_date_data = release_date_soup.find_all(class_="block")
    release_date_data_soup = BeautifulSoup(str(release_date_data), 'html.parser')

    print("Director: " + director_name_soup.string)
    #print(release_date_data_soup)
    print("Release date:")
    for d in release_date_data_soup:
        print(d.string)

    boxoffice = soup.find(class_="boxoffice")
    boxoffice_soup = BeautifulSoup(str(boxoffice), 'html.parser')
    boxoffice_nousa_soup = BeautifulSoup(str(boxoffice.next_sibling), 'html.parser')

    print("boxoffice:")
    print(boxoffice_soup.string)
    print(boxoffice_nousa_soup.string)

    rate = soup.find(class_="filmRating__rateValue")
    rate_soup = BeautifulSoup(str(rate), 'html.parser')

    rate_critic = soup.find(class_="filmRating filmRating--filmCritic")
    rate_critic_soup = BeautifulSoup(str(rate_critic), 'html.parser')
    rate_critic_data = rate_critic_soup.find(class_="filmRating__rateValue")
    rate_critic_data_soup = BeautifulSoup(str(rate_critic_data), 'html.parser')

    print("Film rate:")
    print("Social: " + rate_soup.string)
    print("Critic: " + rate_critic_data_soup.string)


if __name__ == "__main__":
    main()
