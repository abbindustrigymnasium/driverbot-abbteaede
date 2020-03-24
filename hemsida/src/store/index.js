import Vue from "vue";
import Vuex from "vuex";

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    switch: [false, false]
  },
  mutations: {
    engineMotor: (state, switchnumber) => {
      if (state.switch[switchnumber] == true) {
        state.switch[switchnumber] = false;
      } else state.switch[switchnumber] = true;
    }
  },
  actions: {
    engineMotor: ({ commit }, number) => {
      commit("engineMotor", number);
    }
  },
  getters: {
    Switch: state => state.switch
  },
  modules: {}
});
