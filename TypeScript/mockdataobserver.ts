// MOCK SERVICE DATA

import { Injectable } from '@angular/core';
import { Observable, of} from 'rxjs';
import { delay } from 'rxjs/operators';



export class Conatact {

   constructor(public id: number, public name: string);
}


 const CONTACTS Contacts[] =[
 new Contact(21,'Yasha'),
 new Contact(22,'Locate'),
];

 const FETCH_LATENCY = 500;


export class ContactService {

 getContacts(): Observable<Contact[]> {
  return of(CONTACTS).pipe(delay(FETCH_LATENCY));
   }

 getContact(id: number | string) : Observable<Contact[]> {
   const contacts = of(CONTACTS.find(contact => contact.id === +id));
 return contacts$.pipe(delay(FETCH_LATENCY));
    }
}

// MOCK SERVICE COMPONENT 

 @Component ({
   selector: 'app-contact' 
 })

 export class ContactComponent {
   
   constructor(private contactService: ContactService, userService:
        UserService, private fb: FormBuilder) {
    this.userName = userService.userName;
}

  contact: Contact;
  contacts: Contact[];

   msg = 'Loading Contact ...';
   userName = '';


 setupForm() {
  this.contactService.getContacts().subscribe(contacts => {
         this.msg = '';
         this.contacts = contacts;
        this.contact = contacts[0];
       this.contactForm.get('name').setValue(this.contact.name);
 });


// HTML BUTTON FOR next()

<button type="button" class="btn" (click)="next()"
    [disabled]="!contactForm.valid && contactForm.touched">
    Next Contact</button>
