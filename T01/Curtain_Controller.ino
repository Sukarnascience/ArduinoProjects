<!DOCTYPE html>
<html>
    <head>
        <title>Curtain Controller</title>
        <style>
            body{
                text-align: center;
                background-color: #702963;
                color:rgb(255, 255, 255);
                font-size: 35px;
                font-family: "Courier New", Courier, monospace;
            }
            button{
                border-radius: 20px;
                font-size: 45px;
                font-family: "Courier New", Courier, monospace;
                width: 80%;
                padding: 25px;
            }
            div{
                width: 100%;
                height: 100%;
                display: grid;
                column-gap: 50px;
            }
            #open{
                background-color: rgba(0, 255, 149, 0.801);
            }
            #close{
                background-color: rgba(255, 67, 67, 0.801);
            }
        </style>
    </head>
    <body>
        <h1>Curtain Controller</h1>
        <p>Helps you to close/open the Curtain</p>
        <div>
            <a href="/state=close"><button id="close"><b>Close</b></button></a>
            <br>
            <a href="/state=open"><button id="open"><b>Open</b></button></a>
        </div>
        <p>
            &#169; Sukarna Jana 2022
        </p>
    </body>
</html>
