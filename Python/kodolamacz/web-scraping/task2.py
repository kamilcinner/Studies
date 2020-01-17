from bs4 import BeautifulSoup
import requests

def main():
    response = requests.get("https://stooq.pl/q/?s=cdr")

    html_doc = response.text

    soup = BeautifulSoup(html_doc, 'html.parser')

    price = soup.find(id="aq_cdr_c1")
    price_soup = BeautifulSoup(str(price), 'html.parser')

    percentage_change = soup.find(id="aq_cdr_m3")
    percentage_change_soup = BeautifulSoup(str(percentage_change), 'html.parser')

    absolute_change = soup.find(id="aq_cdr_m2")
    absolute_change_soup = BeautifulSoup(str(absolute_change), 'html.parser')

    number_of_transactions = soup.find(id="aq_cdr_n1")
    number_of_transactions_soup = BeautifulSoup(str(number_of_transactions), 'html.parser')

    print("Price: " + price_soup.string)
    print("Percentage change: " + percentage_change_soup.string)
    print("Absolute change: " + str(abs(float(absolute_change_soup.string))))
    print("Number of transactions: " + number_of_transactions_soup.string)


if __name__ == "__main__":
    main()
