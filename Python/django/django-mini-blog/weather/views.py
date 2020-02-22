import requests
from django.shortcuts import render

from weather.forms import CityModelForm
from weather.models import City


def index(request):
    url = 'https://api.openweathermap.org/data/2.5/weather?q={}&units=metric&APPID=cf5059cdaa54103def6a0a166d81330e'

    if request.method == 'POST':
        form = CityModelForm(request.POST)
        if form.is_valid():
            form.save()

    form = CityModelForm()

    cities = City.objects.all()

    weather_data = []

    for city in cities:
        response = requests.get(url.format(city)).json()

        city_weather = {
            'city': city.name,
            'temperature': response['main']['temp'],
            'description': response['weather'][0]['description'],
            'icon': response['weather'][0]['icon']
        }

        weather_data.append(city_weather)

    context = {'weather_data': weather_data, 'form': form}

    return render(request, 'weather/index.html', context=context)