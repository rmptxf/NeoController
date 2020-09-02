import { Component, NgZone } from '@angular/core';
import { NavController, ToastController, LoadingController, AlertController } from '@ionic/angular';
import { ActivatedRoute } from "@angular/router";

import { BLE } from '@ionic-native/ble/ngx';

const pixel_service_uuid = "f4581400-b000-4042-ba50-05ca45ba4512" ; 
const  command_char_uuid = "f4581401-b000-4042-ba50-05ca45ba4512" ;  

@Component({
  selector: 'app-detail',
  templateUrl: './detail.page.html',
  styleUrls: ['./detail.page.scss'],
})
export class DetailPage {

  peripheral: any = {};
  r:number = 0;
  g:number = 0;
  b:number = 0;
  rgb:string = 'rgb(0,0,0)';

  constructor(   
              private ble: BLE,
              private toastCtrl: ToastController,
              public ngZone: NgZone,
              private route: ActivatedRoute,
              public loadingController: LoadingController,
              private alertCtrl: AlertController, 
              public navCtrl: NavController
            ) {
    
    this.route.queryParams.subscribe(params => {
        console.log(params);
        let device = JSON.parse(params['device']);
        this.ble.connect(device.id).subscribe(
            peripheral => this.onConnected(peripheral),
            peripheral => this.onDeviceDisconnected(peripheral)
        );
    });
  }

  ionViewDidLoad() 
  {
        console.log('ionViewDidLoad DetailPage'); 

  }

  ionViewWillEnter() 
  {
        console.log('ionViewWillLoad DetailPage'); 
  }  

  onConnected(peripheral) {

    console.log('Connected to ' + peripheral.name + ' ' + peripheral.id);
    this.ngZone.run(() => {
      this.peripheral = peripheral;
    });
  } 

  setRGBColor($event){
    
    if(this.r > 255) this.r = 255;
    else if(this.r < 0 || this.r === NaN) this.r = 0;

    if(this.g > 255) this.g = 255;
    else if(this.g < 0 || this.g === NaN) this.g = 0;

    if(this.b > 255) this.b = 255;
    else if(this.b < 0 || this.b === NaN) this.b = 0;

    this.rgb = "rgb("+this.r.toString()+", "+this.g.toString()+", "+ this.b.toString()+")";
  
  }

  sendRGBdata() { 
    let data = new Uint8Array([this.r,this.g, this.b]);
      this.ble.write(this.peripheral.id, pixel_service_uuid, command_char_uuid, data.buffer as ArrayBuffer ).then(
          () => this.onUpdateSucced(),
          () => this.onUpdateFailed()
      );
  }  

  disconnect() {

    this.ble.disconnect(this.peripheral.id).then(
            () => {this.onDisconnect();this.navigationBackHome()},
            () => {this.showAlert("ERROR","Error disconnecting !");this.navigationBackHome()}
        );
       
    }

  navigationBackHome(){
    this.navCtrl.navigateBack(['home']);
  }

  async onDeviceDisconnected(peripheral) {
      let toast = await this.toastCtrl.create({
          color: "danger",
          message: 'The Pixel unexpectedly disconnected!',
          duration: 2000,
          position: 'bottom'
      });
      this.navCtrl.navigateBack(['home']);
  
      toast.onDidDismiss().then(() => {
          console.log('Dismissed toast');
      });
   
      toast.present();
  }


  async onDisconnect() {
    let toast = await this.toastCtrl.create({
        color: "danger",
        message: 'Disconnected',
        duration: 1000,
        position: 'bottom'
    });

    toast.onDidDismiss().then(() => {
        console.log('Dismissed toast');
    });

    toast.present();
}

  async showAlert(title, message) {               
    let alert = await this.alertCtrl.create({
          header: title,
          subHeader: message,
          buttons: ['OK']
          })         
    await alert.present();
   }
          

async onUpdateSucced() {
  let toast = await this.toastCtrl.create({
      color: "tertiary",
      message: 'Success!',
      duration: 800,
      position: 'bottom'
  });

  toast.onDidDismiss().then(() => {
      console.log('Dismissed toast');
  });

  toast.present();
}

async onUpdateFailed() {
  let toast = await this.toastCtrl.create({
      color: "danger",
      message: 'Failure!',
      duration: 1000,
      position: 'bottom'
  });

  toast.onDidDismiss().then(() => {
      console.log('Dismissed toast');
  });

  toast.present();
}

}








