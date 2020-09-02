import { Component, NgZone } from '@angular/core';
import { NavController, AlertController,ToastController, LoadingController } from '@ionic/angular';
import { NavigationExtras } from '@angular/router';
import { BLE } from '@ionic-native/ble/ngx';

const pixel_service_uuid = "f4581400-b000-4042-ba50-05ca45ba4512" ; 

@Component({
  selector: 'app-home',
  templateUrl: 'home.page.html',
  styleUrls: ['home.page.scss'],
})
export class HomePage {

  devices: any[] = [];
  
  constructor(private ble: BLE,
              public navCtrl: NavController,           
              private toastCtrl: ToastController,
              private alertCtrl: AlertController,
              private loadingController: LoadingController,
              private ngZone: NgZone) {
             }


  ionViewWillEnter()
  {
      console.log('ionViewWillEnter'); 
      this.blecheck()            
  };
              
              
  ionViewDidLoad() 
  {
      console.log('ionViewDidLoad');
      this.blecheck()
  };
      
           
  scan() 
  {
      this.onscaning();       
      this.devices = [];  // clear existing list
      this.ble.scan([pixel_service_uuid],3).subscribe(
                device => { this.onDiscoveredDevice(device);},
                error =>  { this.showAlert("Error","Error scanning for HID devices");}              
        );                                 
  }                    
       
  blecheck(){                
    this.ble.enable().then(
              () =>  this.scan(),
              () =>  this.bledisabled()
                );                  
              }
            
         
  bledisabled(){  

    this.showAlert("Bluetooth Disabled" , "Please Enable the Bluetooth!");
            
 }   

  onDiscoveredDevice(device) {
      console.log('Discovered ' + JSON.stringify(device, null, 2));
      this.ngZone.run(() => {
              this.devices.push(device);
            });
      }
                             
  deviceSelected(device) { 
        
      console.log(JSON.stringify(device) + ' selected'); 
      let navigationExtras: NavigationExtras = {
            queryParams: {
                device: JSON.stringify(device)
                    }
                };
                
      this.navCtrl.navigateForward(['detail'],navigationExtras);
      this.onDeviceConnected(); 
      
           }
    
            
  async showAlert(title, message) {               
        let alert = await this.alertCtrl.create({
              header: title,
              subHeader: message,
              buttons: ['OK']
              })         
        await alert.present()
       }
                
                              
  async onscaning() {
         const loading = await this.loadingController.create({
                spinner:"bubbles",
                duration: 1000,
                translucent: true,
                mode: "ios",
                cssClass: 'spinner'
                  });
                  return await loading.present();
              }
              
 
  async onDeviceConnected() {
          let toast = await this.toastCtrl.create({             
                color: "primary",
                message: " Connected",
                duration: 1000,
                position: 'bottom'              
                });
              
          toast.onDidDismiss().then(() => {
                  console.log('Dismissed toast');
                });
              
          toast.present();
         }
              

}
