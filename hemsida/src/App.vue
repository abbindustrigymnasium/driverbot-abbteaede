<template>
  <v-app>
    <Toolbar />
    <v-container full height style="height:75%;">
      <v-container
        style="display: flex; align-items: center; align-content: flex-start; flex-direction: column; height: 100%;"
      >
        <v-row>
          <v-col>
            <v-switch
              @change="onoff()"
              v-model="Engine"
              :label="'On/Off engine'"
              align-center
            ></v-switch>
            <body class="noselect" onload="init();">
              <div class="container space-top">
                <h1 class="center blue-text thin">Joystick for steering</h1>
                <div class="center-align">
                  <canvas id="joystick" height="300" width="300"></canvas>
                </div>
                <p id="xVal" class="light">X:</p>
                <p id="yVal" class="light">Y:</p>
              </div>
            </body>
          </v-col>
        </v-row>
      </v-container>
    </v-container>
  </v-app>
</template>

<script>
import Toolbar from "./components/Toolbar";
var mqtt = require("mqtt");
// define(["nipplejs"], function(nipplejs) {
//   var manager = nipplejs.create(optioms);
//});
// var manager = require("nipllejs").create(options);

export default {
  name: "App",

  components: {
    Toolbar
  },

  data: () => ({
    Engine: false,
    user: "tea.edelborg@abbindustrigymnasium.se",
    pass: "Hejsan",
    connected: false
    // src : "https://code.createjs.com/1.0.0/createjs.min.js",
  }),
  mounted() {
    this.connect();
  },
  methods: {
    connect() {
      //funktion som connectar frontend till backend
      var mqtt_url = "maqiatto.com"; //Broker adressen som vi använder
      var url = "mqtt://" + mqtt_url; //definerar det som ska vara innan url:n
      var options = {
        port: 8883, //porten för att publisha
        //genererar ett random clientId för att annars skulle alla få samma
        clientId:
          "mqttjs" +
          Math.random()
            .toString(16)
            .substr(2, 8),
        username: this.user, //användarnamn
        password: this.pass //lösenord
      };
      console.log("connecting");
      this.client = mqtt.connect(url, options);
      console.log("connected?"); //frågar om det har connectat

      this.client
        .on("error", function() {
          console.log("no"); // vid fel consol loggar "no"
        })
        .on("close", function() {
          console.log("no"); // vid fel consol loggar "no"
        });
      this.connected = true;
      console.log(this.connected); //loggar om den har connectat
    },
    onoff() {
      this.$store.dispatch("engineMotor", 0);

      this.client.publish(
        "tea.edelborg@abbindustrigymnasium.se/drive",
        this.Engine == true ? "1" : "0"
      );
    }
  }
};
</script>
<style scoped>
body {
  height: 100%;
  width: 100%;
  background-color: #dedede;
}

.space-top {
  padding-top: 10px;
}

#joystick {
  height: 300px;
  width: 300px;
  border-radius: 300px;
  -moz-border-radius: 300px;
  -webkit-border-radius: 300px;
  text-align: center;
  background-color: #80d5ff;
  font: 24px/300px Helvetica, Arial, sans-serif;
  cursor: all-scroll;
  user-select: none;
  z-index: -100;
}

.noselect {
  -webkit-touch-callout: none;
  -webkit-user-select: none;
  -khtml-user-select: none;
  -moz-user-select: none;
  -ms-user-select: none;
  user-select: none;
}
</style>
