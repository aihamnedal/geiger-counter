// secrets.h - Update this with your own Wi-Fi credentials and AWS IoT information
// AWS IoT Endpoint and Thing Name
const char* AWS_IOT_ENDPOINT = "a3fd8yrmyxwiz7-ats.iot.us-east-2.amazonaws.com";  // Your AWS IoT endpoint
const char* AWS_IOT_THING_NAME = "ESP32_PULSE";  // Your AWS IoT Thing Name

// AWS IoT Certificates (replace with your actual certificates)
const char* AWS_CERT_CA = "-----BEGIN CERTIFICATE-----\n"
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
"ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
"b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"
"MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
"b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
"ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
"9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
"IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
"VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
"93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
"jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
"AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
"A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
"U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
"N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
"o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
"5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
"rqXRfboQnoZsG4q5WTP468SQvvG5\n"
"-----END CERTIFICATE-----\n";  // Your root CA certificate

const char* AWS_CERT_CRT = "-----BEGIN CERTIFICATE-----\n"
"MIIDWjCCAkKgAwIBAgIVAI+g5WywScw3v6kflD3kADV1e6dwMA0GCSqGSIb3DQEB\n"
"CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n"
"IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yNDExMTAwMDM2\n"
"NTNaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n"
"dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCuIfrOeVhaI80i8jn5\n"
"5Na0rvvMSd1Yshf/0Pt2vaFNU7CVGaODiQh1JfSBs7sCkX3QQUk/eu42sC/YW4zV\n"
"2yNig46Q89ZOCbyEVbcukqFB0bu8BACshnTCdB/RSXv6DI/NlMwKIbQvQ7ea2XlU\n"
"97YxkKmGkFl2pLuSbH09QooflOfOBPYazILw1rltzoYbUCtUbkvatSMq340cclyN\n"
"nOtV8F4r9jgMEh6f6taYcfC2NalwBK+3spPygwDhO97pNyPcfzvZkZElinbkGLDn\n"
"oShhZVLXq+qzo4jHu/rL/ebp8cQtQo/FfLZDwJvnwruPTsPnfWZ7HDvAadiBu03v\n"
"1janAgMBAAGjYDBeMB8GA1UdIwQYMBaAFJ+/Iak5qxcKWZ0/8+cUJdNB0XxZMB0G\n"
"A1UdDgQWBBS7pTjz/4A0AMKLes89R++r/s/pNDAMBgNVHRMBAf8EAjAAMA4GA1Ud\n"
"DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAjLnohCSJwbUkI3hBNVPvRSHe\n"
"oLlWIHTC3z9xA7VhGuEhezW2Ks4ZcK7sWtF+K6TNyXMR4QnWGLn3K9GbD5GPBmpy\n"
"tlBIcbPAOIHEDqHiy8Vl5FY8K8soLQRfStTyIhEs/DUsFI27/P8DK2Fn6NW2N0eI\n"
"YDAYeNs9cgIdCAfrWTuIomFUIeCnDT1cWuiGTVskylFkT9VwjSfPl3dbDr0rzxhj\n"
"fMszAN6iZTDojjde7tu0wq4I6q/TVTrrGr8NXqM7Fy0IvPbS0VqgXKMtcF67he5k\n"
"QG1FSvWiqBMHo3a/J4NVU6nfo4oxf0K45zERGHIk/y07DUfwrPFaD/ACSrY6Bw==\n"
"-----END CERTIFICATE-----\n"; // Your device certificate

const char* AWS_CERT_PRIVATE = "-----BEGIN RSA PRIVATE KEY-----\n"
"MIIEpAIBAAKCAQEAriH6znlYWiPNIvI5+eTWtK77zEndWLIX/9D7dr2hTVOwlRmj\n"
"g4kIdSX0gbO7ApF90EFJP3ruNrAv2FuM1dsjYoOOkPPWTgm8hFW3LpKhQdG7vAQA\n"
"rIZ0wnQf0Ul7+gyPzZTMCiG0L0O3mtl5VPe2MZCphpBZdqS7kmx9PUKKH5TnzgT2\n"
"GsyC8Na5bc6GG1ArVG5L2rUjKt+NHHJcjZzrVfBeK/Y4DBIen+rWmHHwtjWpcASv\n"
"t7KT8oMA4Tve6Tcj3H872ZGRJYp25Biw56EoYWVS16vqs6OIx7v6y/3m6fHELUKP\n"
"xXy2Q8Cb58K7j07D531mexw7wGnYgbtN79Y2pwIDAQABAoIBAFVYkC3MqbIcY/mh\n"
"0Sqar2UFcqJQ/azwNPUL/4PWM43L2/toAo2Ah2WrgahkZ989YfXFWdpELSceuYSI\n"
"coGKk1BAfIqtCDddbElMHak08tZormPbbl0g1W9NLR8NrjcDGyQ+rra0iDS2MvIx\n"
"btdnRaQLbBto+oA9AzYj+EojJ8GMEbrCAjKc5naOe//7sVVcIoBIS5Y/aGFjTkm0\n"
"hasqA41J9YJSp9Yrmc0w5TwIXwqagw0rvItsoThlRl1tvJRTBTgk1NbTdwCdI7Yi\n"
"xcD8fbh+P89leeq0B4Uk+1b5WrRDmyJrPqgO8Jf0RPhS4XkrnM5OYSPIt78pIyqA\n"
"xDxk7RkCgYEA30nMxZ1kpo9e5sdci5rEPrZPqdaVtzCIcrVvQJzxTqVlws+jl6/T\n"
"CRhQ0zs/nHAllcFCd82hA6JLfw7NiOEHwX3pQ+l+MEBmG6QQtUazKJFrywPX07tK\n"
"kOiAhnyOpF3fnuMuQrJvdg3tW6xbmiwXVs6EtU7RGfUlyj+FxiZZBi0CgYEAx6Sm\n"
"pOSK/c199IjIqgm4W323P7QY7ed8bbghhOfdvqmozF+AXTtHkn2oWwJb9pJ7Pg+a\n"
"J/s13H9AQosr8GZYIT0KTgPavvqMRd1iYs70JXhasl2NrGleXLB8KGXO9vK0Tiic\n"
"XrWVnCjPvqlGzmepuup7VJ4g0NZMC/+AeylZaKMCgYEAmj9oFweglTMrku8brlEO\n"
"yme05pWXPUJosB1IKnGAfRzjDE3WLB5JAdprU1B1pAMQ47/qw8ooNdNypeY69BjH\n"
"+9GYR9LP2lNSdjvDUwbxEtBKj6cq/FhArZP/3WfEPiWfKiq0NV0AhKQgWRja+skE\n"
"onHt2TYGWxEvtuRk7Dpne00CgYEAh8vlVk/mgxDd1hGcfJyz+/edSAWW12wX5QHU\n"
"OvUEjgYVPT7Qr5n86xXyCEWojCXDEsnGD9/+GQetjBXiQ1k6JRHCCqLwjesaswMN\n"
"QyyGQV6GQsED9vyNJPse2NO3XZ5lKqzRAFL/ewL/nC7EbO1yNCP+0+XjaGn7vEWE\n"
"/UF5AYUCgYBlDtXXQgYBfi2VwqOVpnKw9BMpealyV8VpqGqJMuooSnaAssBWVRIm\n"
"v2iBZ1dX/kB540DI6VISUykULacR9GEcAXCY1qGpGdujLvXKtHXv9ir7ArFksPYY\n"
"ys9YNSLyGe1oXbWC24wzRshmbZVNe7L/8UiKJUba0d/ntX494uG6FA==\n"
"-----END RSA PRIVATE KEY-----\n"; // Your private key