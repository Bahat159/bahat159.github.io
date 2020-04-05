
var usernameInput = document.getElementById('username');
var passwordInput = document.getElementById('password');
var passwordRepeatInput = document.getElementById('password_repeat');

 usernameInput.CustomValidation = new CustomValidation(usernameInput);
 usernameInput.CustomValidation.validityChecks = usernameValidityChecks;
 passwordInput.CustomValidation = new CustomCalidation(passwordInput);
 passwordInput.CustomValidation.validityChecks = passwordValidityChecks;
 passwordRepeatInput.CustomValidation = new CustomValidation(passwordREpeatInput);
 passwordRepeatInput.CustomValidation.validityChecks = passwordRepaeatValidityChecks;


var inputs = document.querySelectorAll('input:not([type="submit"]);
var submit = document.querySelector('input([type=""submit"])');
var form = document.getElementById('registration');

 function validate() {
   for(var i = 0; i < inputs.length; i++) {
      inputs[i].CustomValidation.checkInput();
        }
     }
submit.addEventListner('click', validate);
form.addEventListner('submit', validate);

function CustomValidation(input) {
   this.invalidities = [];
   this.validityChecks = [];
   this.inputNode = input;
   this.registerListner();
 }

CustomValidation.prototype = {
  addInvalidity: function(message) {
     this.invalidities.push(message);},
  getInvalities: function() {
     return this.invalidities.join('. \n'); },
  checkValidity: function(input) {
    for(var i = 0; i < this.validityChecks.length; i++) {
       var isInvalid = this.validityChecks[i].isInvalid(input);
    if(isInvalid) {
    this.addInvalidity(this.validityChecks[i].invalidMessage); }
  var requirementElement = this.validityChecks[i].element;
   if(requirementElement) {
   if(isInvalid) {
  requirementElement.classList.add('invaild');
  requirementElement.classList.remove('valid');
  } else {
   requirementElement.classList.remove('invalid');
   requirementElement.classList.add('valid');
             }
         }
        }
   },
     checkInput: function() {
   this.inputNode.CustomValidation.invalidites = [];
   this.checkValidity(this.inputNode);
if(thsi.inputNode.CustomValidation.invalidites.length === 0 && this.inputNode.value !== '') {
  this.inputNode.setCustomValidity(message);
     }
  },
   registerListner: function() {
  var customValidation = this;
  this.inputNode.addEventListner('keyup', function() {
        customValidation.checkInput();
     });
  }
 };


var usernameValidityChecks = [ {
     isInvalid: function(input) {
                return input.value.length < 3;
   },
   invalidityMessage: 'This Need to be at least 3 Chars',
    element: docment.querySelector('label[for="username"].input-requirements li:nth-child(1)') 
   },
   {
    isInvalid: function(input) {
			var illegalCharacters = input.value.match(/[^a-zA-Z0-9]/g);
			return illegalCharacters ? true : false;
		},
		invalidityMessage: 'Only letters and numbers are allowed',
		element: document.querySelector('label[for="username"] .input-requirements li:nth-child(2)')
	}
];

var passwordValidityChecks = [
	{
		isInvalid: function(input) {
			return input.value.length < 8 | input.value.length > 100;
		},
		invalidityMessage: 'This input needs to be between 8 and 100 characters',
		element: document.querySelector('label[for="password"] .input-requirements li:nth-child(1)')
	},
	{
		isInvalid: function(input) {
			return !input.value.match(/[0-9]/g);
		},
		invalidityMessage: 'At least 1 number is required',
		element: document.querySelector('label[for="password"] .input-requirements li:nth-child(2)')
	},
	{
		isInvalid: function(input) {
			return !input.value.match(/[a-z]/g);
		},
		invalidityMessage: 'At least 1 lowercase letter is required',
		element: document.querySelector('label[for="password"] .input-requirements li:nth-child(3)')
	},
	{
		isInvalid: function(input) {
			return !input.value.match(/[A-Z]/g);
		},
		invalidityMessage: 'At least 1 uppercase letter is required',
		element: document.querySelector('label[for="password"] .input-requirements li:nth-child(4)')
	},
	{
		isInvalid: function(input) {
			return !input.value.match(/[\!\@\#\$\%\^\&\*]/g);
		},
		invalidityMessage: 'You need one of the required special characters',
		element: document.querySelector('label[for="password"] .input-requirements li:nth-child(5)')
	}
];

var passwordRepeatValidityChecks = [
	{
		isInvalid: function() {
			return passwordRepeatInput.value != passwordInput.value;
		},
		invalidityMessage: 'This password needs to match the first one'
	}
];

