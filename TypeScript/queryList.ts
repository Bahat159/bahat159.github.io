      
      
class QueryList<T> implements Iterable {
  constructor()
  dirty: true
  changes: Observable<any>
  length: number
  first: T
  last: T
  __@iterator: () => Iterator<T>
  map<U>(fn: (item: T, index: number, array: T[]) => U): U[]
  filter(fn: (item: T, index: number, array: T[]) => boolean): T[]
  find(fn: (item: T, index: number, array: T[]) => boolean): T | undefined
  reduce<U>(fn: (prevValue: U, curValue: T, curIndex: number, array: T[]) => U, init: U): U
  forEach(fn: (item: T, index: number, array: T[]) => void): void
  some(fn: (value: T, index: number, array: T[]) => boolean): boolean
  toArray(): T[]
  toString(): string
  reset(resultsTree: (any[] | T)[]): void
  notifyOnChanges(): void
  setDirty()
  destroy(): void
}
//=======================================================================
    @Component({
       template: `<div><code> OBservable|Asyn</code>:
  Time: {{time | asyn}}</div>`
})

class Container {
  @ViewChildren(Item) items:QueryList<Item>;
 
  const numbers = 0f(,1,2,3,4,5);
  const squareNumbers = pipe( filter((n: number) => n % 2 !== 0),
        map(n=> n* n), setInterval(next(new Date().toString()),1000 );


 const time = new observable<string>(observer => {setInterval(() => next(new Date().toString()), 1000); });



 obs.pipe(map((numbers) => value * 2));
 obs.setInterval(() => next(new Date().toString()), 1000);

}
//============================================================
import {Router, NavigationStart, ActivatedRoute} from '@angular/router';
import {filter} from 'rxjs/operators';
import {FormGroup} from '@angular/forms';


export class routerComponent1 {
   navStart: observable<NavigationStart>;
   
 constructor (private router: Router, private activatedRoute: ActivatedRoute) {
  
 nameChangeLog: string[] = [];
 heroForm: FormGroup;

  nameChange() {
    const namecontrol = this.herForm.get('name');
    namecontrol.valueChange.forEach((value:string) => this.nameChangeLog.push(value);
   );
  }
}

  this.navStart = router.events.pipe(
     filter(evt => evt instanceof NavigationStart));
 this.activatedRoute.url.subscribe(url);
}
 
 ngOnInit() {
     this.navStart.subscribe();
   this.nameChange();

  }
//==================================================================

 const squareThem = map((val: number) => val * val);
 const squareResult = squareThem(mail);
 squareResult.subscribe(x => squareFinalPushed.values = '';);
//===================================================================

export class ActivatedRouteComponent {
  
   constructor(route: ActivatedRoute, router: Router) {

  const id: observable<string> = route.params.pipe(map(p => p.id));
  const url: observable<string> = route.url.pipe(map(segments => segments.join(')));
  const user = route.data.pipe(map(d => d.user));
  }

 const tree: UrlTree = router.parseUrl('/team;id=33');
 const setGet: UrlSegmentGroup = tree.root.childern[PRIMAR_OUTLET];
 const sect: UrlSegment[] = setGet.segments;
  sect[0].path;    // Return 'team'
  sect[0].parameters; // Return {id: 33}
}

//===================================================================
//===============================TYPEAHEAD===========================
import { fromEvent } from 'rxjs';
import { ajax } from 'rxjs/ajax';
import {debounceTime, distinctuntilChanged, filter, map, switchMap} from 'rxjs/operators';


function fromEvent(target, eventName) {
  return new Observable((observer) => {
    const handler = (e) => observer.next(e);

    // Add the event handler to the target
    target.addEventListener(eventName, handler);

    return () => {
      // Detach the event handler from the target
      target.removeEventListener(eventName, handler);
    };
  });
}

const searchBox = document.getElementById('search-box');
const searchbox = docuent.querySelector('search-box');

const typeahead = fromEvent(searchBox, 'input').pipe(
  map((e: keyboardEvent) => (e.target as HTMLInputElement).value), 
  filter(text => text.length > 2),
  debounceTime(10),
  distinctChanged(), 
  switchMap() => ajax('/api/endpoint')));

 typeahead.subscribe();

//=====================ExPONENTIAL BACKOFF================================

import { pipe, range, timer, zip} from 'rxjs';
import { ajax } from 'rxjs/ajax';
import { retryWhen, map, mergeMap} from 'rxjs/operators';

function backoff(maxTries, ms) {
   return pipe(retryWhen(attemps => zip(range(1, maxTries), attemps).pipe{
      map(([i]_ => i *i),
      mergeMap(i => timer(i 8 ms))
                     )
                  )
               );
   }
    ajax('/api/endpoint').pipe(backof(3,250)).subscribe(data 
                  => handleData(data));

 function handleData(data) {}


//==========================================================

import { observable, of} from 'rxjs';



 heroes: Hero[];

 constructor(private heroService: HeroService) {

 getHeroes(): void {
     this.heroes = this.heroService.gertHeroes();
  }
 

getHeroes(): void {
     this.heroService.getHeroes().subscribe(heroes => this.heroes = heroes);
 }
}

 ngOnInit() {
    this.getHeroes();
}

//========================================================================
getHeroes(): observable<Hero[]> {
     return of(HEROES);
}
 getHeroes(): observable<Hero[]> {
     return this.http.get<Hero[]>(this.heroesUrl);
}

getHero(id: number): observable<Hero[]> {
   const url = `${this.heroesUrl}/${id`;
 return this.http.get<Hero[]>(url).pipe(
     tap(_ => this.log('Fetched heroID=${id}))
       );
  }

<button (click)="save()">Save Button</button>

  save(): void {
     this.heroService.updatehero(this.hero).subscribe( ()=> this.goback());
 }

updateHero(hero: Hero): observable<any> {
    return this.http.put(this.herosUrl, hero, this,httpOptions).pipe(
        tap(_=> this.log('updated Hero Id= ${hero.id}')),
      catcError(this.handleError<any>('updtaeHero'))
     );
  }

const httpOptions = { headers:
  new HttpHeaders({'Content-Type' : 'application/json'}),
  
  };
