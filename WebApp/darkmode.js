window.addEventListener('load',function(){
    var element = document.body;
    if(localStorage.getItem("darkmode")=='on'){
        element.classList.add("darkback");
        localStorage.setItem("darkmode", "on");
        document.getElementById('toggle').checked=true;

        document.getElementsByTagName('h2')[0].style.color='wheat';
        document.getElementsByTagName('h5')[0].style.color='wheat';
        for(let i=0; i<document.getElementsByTagName('h3').length;i++){
            document.getElementsByTagName('h3')[i].style.color='wheat';
        }
        for(let i=0; i<document.getElementsByTagName('p').length;i++){
            document.getElementsByTagName('p')[i].style.color='wheat';
        }

    }
    else{
        element.classList.remove("darkback");
        localStorage.setItem("darkmode", "off");
        element.style.color='black';
        document.getElementById('toggle').checked=false;

        document.getElementsByTagName('h2')[0].style.color='black';
        document.getElementsByTagName('h5')[0].style.color='black';
        for(let i=0; i<document.getElementsByTagName('h3').length;i++){
            document.getElementsByTagName('h3')[i].style.color='black';
        }
        for(let i=0; i<document.getElementsByTagName('p').length;i++){
            document.getElementsByTagName('p')[i].style.color='black';
        }
    }


    var onoffbtn=document.getElementsByTagName('button');
    for(let i=0;i<onoffbtn.length;i++){
        if(onoffbtn[i].textContent=='ON'){
            onoffbtn[i].style.background='#95efb6';
            onoffbtn[i].style.border='2px solid #95efb6';
        }
        else if(onoffbtn[i].textContent=='OFF'){
            onoffbtn[i].style.background='#787979';
            onoffbtn[i].style.border='2px solid #787979';
        }

    }


});




function ToggleDarkMode(){
    var bodybackground = document.body;
    if(document.getElementById('toggle').checked==true){
        bodybackground.classList.add("darkback");
        localStorage.setItem("darkmode", "on");

        document.getElementsByTagName('h2')[0].style.color='wheat';
        document.getElementsByTagName('h5')[0].style.color='wheat';
        for(let i=0; i<document.getElementsByTagName('h3').length;i++){
            document.getElementsByTagName('h3')[i].style.color='wheat';
        }
        for(let i=0; i<document.getElementsByTagName('p').length;i++){
            document.getElementsByTagName('p')[i].style.color='wheat';
        }
    }
    else if (document.getElementById('toggle').checked==false){
        bodybackground.classList.remove("darkback");
        localStorage.setItem("darkmode", "off");

        document.getElementsByTagName('h2')[0].style.color='black';
        document.getElementsByTagName('h5')[0].style.color='black';
        for(let i=0; i<document.getElementsByTagName('h3').length;i++){
            document.getElementsByTagName('h3')[i].style.color='black';
        }
        for(let i=0; i<document.getElementsByTagName('p').length;i++){
            document.getElementsByTagName('p')[i].style.color='black';
        }
    }
}