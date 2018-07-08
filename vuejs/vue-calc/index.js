Vue.component('view-content', {
  template: `<div class="view-box">
                <div class="view-area">{{ this.result }}</div>
             </div>`,
  props: {
    result: {
      type: String,
    },
  }
});

Vue.component('button-content', {
  template: `<button @click="this.clickEvent" v-bind:class="[this.isZero, this.isTop, this.isOpr]">{{ this.name }}</button>`,
  props: {
    name: {
      type: String,
    },
    index: {
      type: Number,
    },
    result: {
      type: String,
    },
    flagOpr: {
      type: Function,
    },
    setView: {
      type: Function,
    },
    initialize: {
      type: Function,
    },
    pushNumStack: {
      type: Function,
    },
    pushOprStack: {
      type: Function,
    },
    equalTo: {
      type: Function,
    },
    changeSig: {
      type: Function,
    },
  },
  data: function() {
    return {
      isZero: this.name === '0' ? 'zeroButton' : '',
      isTop: this.index < 3 ? 'topButton' : '',
      isOpr: (this.index + 1) % 4 === 0 ||
             this.index === 18
             ? 'oprButton'
             : '',
    };
  },
  methods: {
    clickEvent() {
      if(this.name === 'AC') {
        this.initialize();
      } else if(
        this.name === '-' ||
        this.name === '+' ||
        this.name === '×' ||
        this.name === '%' ||
        this.name === '÷' ) {
        this.pushNumStack(this.result);
        this.pushOprStack(this.name);
        this.flagOpr();
      } else if(this.name === '+/-') {
        this.changeSig(this.result);
      } else if(this.name === '=') {
        this.pushNumStack(this.result);
        this.equalTo(this.name);
        this.flagOpr();
      } else {
        this.setView(this.name);
      }
    },
  },
});


new Vue({
  el: '#app',
  data: {
    result: '',
    buttonList: ['AC','+/-','%','÷',
                  '7', '8', '9', '×',
                  '4', '5', '6', '-',
                  '1', '2', '3', '+',
                  '0', '.', '='],
    oprStack: [],
    numStack: [],
    isOpr: false,
  },
  methods: {
    setView(name) {
      let temp = '';
      if(this.isOpr) {
        this.result = name;
        this.flagOpr();
      } else {
        this.result += name;
      }
      temp = this.result;
    },
    //
    flagOpr() {
      this.isOpr = !this.isOpr;
    },
    // 실시간으로 결과를 보여주는 함수
    liveCalc(opr) {
      let data1 = parseFloat(this.numStack.pop());
      let data2 = parseFloat(this.numStack.pop());
      let result = 0;
      switch(opr) {
        case '+':
          result = data2 + data1;
          break;
        case '-':
          result = data2 - data1;
          break;
        case '×':
          result = data2 * data1;
          break;
        case '÷':
          result = data1 === 0 ? '오류' : data2 / data1;
          break;
        case '%':
          result = data1 === 0 ? '오류' : data2 % data1;
          break;
      }
      this.numStack.push(result);
      this.result = result + '';
    },
    // AC 초기화
    initialize() {
      this.oprStack = [];
      this.numStack = [];
      this.result = '';
    },
    // 연산자의 우선순위를 정하는 함수
    getPriority(data) {
      switch(data) {
        case '×':
        case '%':
        case '÷':
          return 2;
        case '+':
        case '-':
          return 1;
      }
      return -1;
    },
    // 연산자 우선순위에의해 반복계산해야하는 경우
    iterateCalc() {
      let symbol = this.oprStack.pop();
      while(symbol) {
        this.liveCalc(symbol);
        symbol = this.oprStack.pop();
      }
    },
    // = : 스택에 존재하는 연산들을 모두 수행
    equalTo() {
      this.iterateCalc();
      this.flagOpr();
      this.oprStack = [];
    },
    // 연산자 우선순위에 따라 스택에 연산자를 넣는 경우를 나누었음
    calcPath(data) {
      // 들어온 연산자가 기존의 연산자보다 우선순위가 낮을경우, 스택에 쌓여져있던것들을 연산 후 push
      if(this.getPriority(this.oprStack[this.oprStack.length - 1]) > this.getPriority(data)) {
        this.iterateCalc();
        this.oprStack.push(data);
      // 연산자 우선순위가 같을 경우 연산 후 push
      } else if(this.getPriority(this.oprStack[this.oprStack.length - 1]) === this.getPriority(data)) {
        this.liveCalc(this.oprStack.pop());
        this.oprStack.push(data);
      // 들어온 연산자가 기존의 연산자보다 우선순위가 높을경우 push 만 해줌
      } else if(this.getPriority(this.oprStack[this.oprStack.length - 1]) < this.getPriority(data)) {
        this.oprStack.push(data);
      }
      // 초기에 연산자스택에 연산자가 아무것도 없을 경우에 push
      if(this.oprStack.length === 0) {
        this.oprStack.push(data);
      }
    },
    // +/- : 부호를 바꿔주는 함수
    changeSig(data) {
      this.result = -data + '';
    },
    // 숫자를 저장하는 스택에 push
    pushNumStack(data) {
      this.numStack.push(data);
    },
    // 연산자를 저장하는 스택에 push 해주는데 calcPath 에 따라 push 타이밍을 달리해줌
    pushOprStack(data) {
      this.calcPath(data);
    },
  },
});