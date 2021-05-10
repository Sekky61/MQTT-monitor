Projekt ICP

Autoři: xmajer21 xpoucp01

spuštění MQTT exploreru:
./build/MQTTexplorer

examples

examples/simulator
obsahuje konfigurační soubory ke spuštění simulátoru provozu
Upozornění: cesty v konfiguračním souboru jsou relativní - nejjednodušši je simulaci spouštet ze složky, kde jsou soubory umístěny

příklad spuštění simulátoru:

cd examples/simulator
../../build/mqttsim tcp://localhost:1888 test_config.cfg
