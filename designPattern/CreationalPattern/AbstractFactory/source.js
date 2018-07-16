// Abstract Factory
class CarFactory {
  // Factory Method
  createCar(model) {
    let car = null;
    switch(model) {
      case 'Cayman':
        car = new Cayman();
        break;
      case 'Boxster':
        car = new Boxster();
        break;
      case 'Panamera':
        car = new Panamera();
        break;
      default:
        car = new Cayman();
        break;
    }
    if(typeof car.printModel === 'undefined') {
      car.printModel = () => {
        console.log(`This car model is: ${car.model}`);
      }
    }
    return car;
  }
}

// Car를 상속받는 Caymen, Boxster, Panamera 팩토리
// 각 팩토리에 맞게 오버라이딩하여 재구현
class Car {
  constructor(name) {
    this.model = name;
  }
  // Abstract Product
  createDoor() {}
  createHood() {}
}

class Door {
  constructor(side, name) {
    this.name = name;
    this.side = side;
  }
  build() {
    console.log(`Build a ${this.side} door for ${this.name}`);
  }
}

class Hood {
  constructor(name) {
    this.name = name;
  }
  build() {
    console.log(`Build a hood for ${this.name}`);
  }
}

// Concrete Factory
class Cayman extends Car{
  constructor() {
    super('Cayman');
  }
  // Concrete Product
  createDoor(side) {
    return new CaymanDoor(side, this.constructor.name);
  }
  // Concrete Product
  createHood() {
    return new CaymanHood(this.constructor.name);
  }
}

// Concrete Factory
class Boxster extends Car{
  constructor() {
    super('Boxster');
  }
  // Concrete Product
  createDoor(side) {
    return new BoxsterDoor(side, this.constructor.name);
  }
  // Concrete Product
  createHood() {
    return new BoxsterHood(this.constructor.name);
  }
}

// Concrete Factory
class Panamera extends Car{
  constructor() {
    super('Panamera');
  }
  // Concrete Product
  createDoor(side) {
    return new PanameraDoor(side, this.constructor.name);
  }
  // Concrete Product
  createHood() {
    return new PanameraHood(this.constructor.name);
  }
}

class CaymanDoor extends Door {
  constructor(side, name) {
    super(side, name);
  }
}
class BoxsterDoor extends Door {
  constructor(side, name) {
    super(side, name);
  }
}
class PanameraDoor extends Door {
  constructor(side, name) {
    super(side, name);
  }
}

class CaymanHood extends Hood {
  constructor(name) {
    super(name);
  }
}
class BoxsterHood extends Hood {
  constructor(name) {
    super(name);
  }
}
class PanameraHood extends Hood {
  constructor(name) {
    super(name);
  }
}


const factory = new CarFactory();

// Client
const boxsterCar = factory.createCar('Boxster');

boxsterCar.printModel();
boxsterCar.createDoor('right').build();
boxsterCar.createDoor('left').build();
boxsterCar.createHood().build();

/* output

This car model is: Boxster
Build a right door for Boxster
Build a left door for Boxster
Build a hood for Boxster

*/