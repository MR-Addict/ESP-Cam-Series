function CapPhoto() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/capturePhoto", true);
  xhr.send();
  location.reload();
}
