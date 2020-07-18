// Initialize Firebase (ADD YOUR OWN DATA)
var config = {
  apiKey: "AIzaSyApiwz9XTonCWDa5IxtIdobGsgbpxUy1A0",
    authDomain: "fir-2612a.firebaseapp.com",
    databaseURL: "https://fir-2612a.firebaseio.com",
    projectId: "fir-2612a",
    storageBucket: "fir-2612a.appspot.com",
    messagingSenderId: "1028626887052",

};
firebase.initializeApp(config);

// Reference messages collection
var messagesRef = firebase.database().ref('messages');

// Listen for form submit
document.getElementById('contactForm').addEventListener('submit', submitForm);

// Submit form
function submitForm(e){
  e.preventDefault();

  // Get values
  var name = getInputVal('name');
  var company = getInputVal('company');
  var email = getInputVal('email');
  var phone = getInputVal('phone');
  var message = getInputVal('message');

  // Save message
  saveMessage(name, company, email, phone, message);

  // Show alert
  document.querySelector('.alert').style.display = 'block';

  // Hide alert after 3 seconds
  setTimeout(function(){
    document.querySelector('.alert').style.display = 'none';
  },3000);

  // Clear form
  document.getElementById('contactForm').reset();
}

// Function to get get form values
function getInputVal(id){
  return document.getElementById(id).value;
}

// Save message to firebase
function saveMessage(name, company, email, phone, message){
  var newMessageRef = messagesRef.push();
  newMessageRef.set({
    Item:name,
    Quantity:company,
    email:email,
    Table:phone,
    Instructions:message
  });
}