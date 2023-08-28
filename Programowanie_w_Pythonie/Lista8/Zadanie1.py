import requests
import json

#pierwszy serwis to Open-meteo, zajmujacy sie prognozami pogody
#drugi serwis (wymagajacy API-key) to number-verification zajmujacy sie weryfikowaniem numerow telefonow

def jprint(obj):
    text = json.dumps(obj, indent=1)
    print(text)

def get_data(url, parameters):
    res = requests.get(url, params=parameters)
    if(res.status_code != 200):
        print("Operacja nie powiodla sie")
    else:
        jprint(res.json())


#serwis pierwszy
print("Serwis Open-meteo:")
parameters_meteo = {
    "latitude":  51.06,
    "longitude": 17.02,
    "current_weather": True 
}
get_data("https://api.open-meteo.com/v1/forecast", parameters_meteo)


#serwis drugi
print("\nSerwis Number-verification:")
key_file = open("api_key.txt", "r")
apikey = key_file.read()
parameters_num_ver = {
    "apikey": apikey,
    "number": "+48123456789"
}
get_data("https://api.apilayer.com/number_verification/validate", parameters_num_ver)
