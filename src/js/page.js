function changePic() {
    var picBtn = document.getElementById("btn");
    document.addEventListener("click", function() {
        var pic = document.getElementById("show-pic");
        var pa = document.getElementById("pic-container");
        pa.removeChild(pic);
        var nPic = document.createElement("img");
        nPic.src = "https://ss3.bdstatic.com/70cFv8Sh_Q1YnxGkpoWK1HF6hhy/it/u=90999730,16539575&fm=23&gp=0.jpg";
        pa.append(nPic);
    });
}
window.onload = function() {
    changePic();
}
