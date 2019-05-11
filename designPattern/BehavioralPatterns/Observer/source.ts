interface IObserver {
    update: Function;
}

interface ISubject {
    observerList: IObserver[];
    subscribe: Function;
    unsubscribe: Function;
    publish: Function;
}

class Subject implements ISubject {
    observerList: Observer[] = [];

    subscribe(observer: Observer): void {
        if (!this.observerList.some((obs: Observer) => obs === observer)) {
            this.observerList.push(observer);
        }
    }

    unsubscribe(observer: Observer): void {
        const findedIndex = this.observerList.indexOf(observer);
        if (findedIndex !== -1) {
            this.observerList.splice(findedIndex, 1);
        }
    }

    publish(data: any): void {
        this.observerList.forEach((observer: Observer) => {
            observer.update(data);
        })
    }
}

class Observer implements IObserver {
    update(data?: any): void {
        console.log('update data is', data);
    }
}

class EmailServer extends Subject {
    sendEmail(message: string): void {
        this.publish(message);
    }
}

class Client extends Observer {
    update(data: string) {
        console.log('메일을 전송받았습니다', data);
    }
}

const emailServer = new EmailServer();

const client1 = new Client();
const client2 = new Client();
const client3 = new Client();

emailServer.subscribe(client1);
emailServer.subscribe(client2);
emailServer.subscribe(client3);

emailServer.sendEmail('first mail');

emailServer.unsubscribe(client2);

emailServer.sendEmail('second mail');

/*

메일을 전송받았습니다 first mail
메일을 전송받았습니다 first mail
메일을 전송받았습니다 first mail

메일을 전송받았습니다 second mail
메일을 전송받았습니다 second mail

*/
