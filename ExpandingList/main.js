class ExpandingList extends HTMLUListElement {
   constructor();
  self = super();
// or super();
// use var Or const to declare variables
 const uls = Array.from(self.querySelectorAll('ul'));
 const lis = Array.from(self.querySelectorall('li'));

// Hide all child uls
 // These lists will be shown when the user clicks a higher level container
 uls.forEach(ul => {
            ul.style.display = 'none';
        });
lis.forEach(li => {
//search for UL child in LI elements and add a click handler
       if(li.querySelectorAll('ul').length > 0) {
    li.setAttribute('class', 'closed');
    
 const childText = li.childNode[0];
 const newSpan = document.createElement('span');

// https://developer.mozilla.org/en-US/docs/Web/CSS/cursor
// To lookup cursor info
//click handler to this span
 newSpan.textContent = childText.textContent;
 newSpan.style.cursor = 'pointer'; 
 newSpan.onclick = self.showul;

 // Add the span and remove the bare text node from the li
childText.parentNode.insertBefore(newSpan, childText);
childText.parentNode.removeChild(childText);
      }
    });
 }

 showul = function(e) {
   const nextul = e.target.nextElementSibling;

  if(nextul.style.display == 'block') {
     nextul.style.dispaly = 'none';
     nextul.parentNode.setAttribute('class', 'closed');
   } else {
          nextul.style.display = 'block';
          nextul.parentNode.setAttribute('class', 'open');
        }
    };
  }
//Define Our New Elements
  customElements.define('expanding-list', ExpandingList, { extends: 'ul'});
