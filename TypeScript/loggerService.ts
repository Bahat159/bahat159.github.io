// user Service

 @Injectable ({
 providedIn: 'root'
  })

 export class UserService {
     
  getUserById(userId: number): any {
    return {name: 'Bombosta', role: 'Admin'};
    }
}


//========================================================================
// User COntext Service

 @Injectable({
     providedIn: 'root';
  })

 class UserContextService {
  name: string;
  role: string;
  loggedInSince: Date;

  constructor(private userService: UserService, private loggerService: LoggerService) {
      this.loggedInSince = new Date();
 }

 loadUser(userId: number) {
  let user = this.userService.getUserById(userId);
  this.name = user.name;
  this.role = user.role;

 this.loggerService.logDebug('Loaded user');
  }
}



//======================================================================
// Logger Service

 @Injectable({
       providedIn: 'root'
   })

class LoggerService {
 logs: string[] = [];

 logInfo(msg: any) { this.log('INFO: ${msg}'); }
 logDebug(msg: any) { this.log('DEBUG: ${msg}'); }
 logError(msg: any) { this.log('Error: ${msg}'); }

 private log(msg: any isErr = false) {
  this.logs.push(msg);
  isErr? console.error(msg): console.log(msg);
  }
}

//==========================================================================
// LoggerService In Action

 constructor(logger: LoggerService, public userContext: UserContextService){
   userContext.loadUser(this.userId);
   logger.logInfo('AppComponent initialized');
 }

//======================================================================
// Hero Service

 @Injectable ({
  providedIn: 'root'
  })

 export class Hero {
     constructor (
      public id: number,
      public name: string,
      public description?: string,
      public phone?: string) {}
 }


 class HeroService {

  private heroes: Array<Hero> = [
    new Hero(1, 'RubberMan', 'Hero of many talents', '123-456-7899'),
    new Hero(2, 'Magma', 'Hero of all trades', '555-555-5555'),
    new Hero(3, 'Dr Nice', 'The name says it all', '111-222-3333')
 ];

 getHeroById(id: number): Hero {
     return this.heroes.find(hero => hero.id === id);
 }

 getAllHeroes(): Array<Hero> {
 return this.heroes;
    }
}

//===================================================================
// RunnerUp Component

 export const RUNNERS_UP = new InjectionToken<string>('RunnersUp');

 export function runnersUpFactory(take: number) {
  return (winner: Hero, heroService: HeroService): string => {
     return heroService.getAllHeroes().filter((hero) => 
            hero.name !== winner.name).map(herp => hero.name)
            .slice(0, Math.max(0, take)).join(' , ');
    };
  }: 


//========================================================================
/*  limit the scope of an injected service to a branch of the application hierarchy by providing that service at the sub-root component for that branch. 
*/


 @Component ({
    selector: 'app-unsorted-heroes',
    providers: [HeroService]
 })

 export class HeroBaseComponent implements OnInint {
    constructor(private heroService: HeroService) {}
    heroes: Array<Hero>;

   ngOnInit() {
   this.heroes = this.heroService.getAllHeros();
   this.afterGetHeroes();
  }
     protected afterGetHeroes() {}
}

 @Component ({ 
    selector: 'app-sorted-heroes',
    providers: [HeroService] 
  })

 export class SortedHeroesComponent extend HeroBaseComponent {
    constructor(heroService: HeroService) {
      super(heroService);
  }

  protected afterGetHeroes() {
 this.heroes = this.heroes.sort(h1,h2) =>{
      return h1.name < h2.name ? -1 : (h1.name > h2.name ? 1 : 0);
     });   
  }
}

//=========================================================================
//  Hero-Cache Service

 @Injectable()
  export class HeroCacheService {
    hero: Hero;
   constructor(private heroService: HeroService) {}
 
  fetchCachedHero(id: number) {
   if(!this.hero) {
      this.herp = this.heroService.getHeroById(id);
    }
    return this.hero;
    }
}

//=========================================================================
// LIMITING HOST COMPONENT SEARCH DEPT WITH @Host or using @Optional
// To check for dependency 

 @Component ({
      selector: 'app-hero-contact',
     tempate: ` 
   <div>Phone #: {{phoneNumber}}
   <spam *ngIf="hasLogger">!!!</span></div>`
  })

 export class HeroContactComponent {
   hasLogger = false;
  
  constructor(@Host() private heroCache: HeroCacheService,
              @Host() @Optional() private loggerService?: LoggerService)
  {
    if(loggerService) {
   this.hasLogger = true;
   loggerService.logInfo('HeroContactComponent can Log');
   }
}
   get PhoneNumber() {
         return this.heroCache.hero.phone}
}
 
 
