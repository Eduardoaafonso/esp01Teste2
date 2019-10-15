const char VERIF_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  <link href="data:image/png;base64,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" rel="icon" type="image/x-icon" />
  <title>Fikiria</title>
  
</head>

<style>
.card{
     max-width: auto;
     min-height: auto;
     background: #008969;
     padding: 20px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
     transition: 0.3s;
}

.cardFundo{
     max-width: auto;
     min-height: auto;
     background: #15343f;
     padding: 20px;
     color: #FFF;
     box-sizing: border-box;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
.card:hover {
    box-shadow: 0 16px 32px 0 rgba(0,0,0,0.2);
}


.grid-container{
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
    grid-gap:10px;
    justify-content: center;
    align-items: center;
    display: flex;
    flex-direction: row;
  }

  .grid-containerFundo{
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(300px, 1fr));
    grid-gap:10px;
    justify-content: center;
    align-items: center;
    display: flex;
    flex-direction: row;
  }

  footer {
    padding: 10px 20px;
    background: #ffffff; <!--"15343f"-->
    color: black;
  }

body {
   background-color: #ffffff;
   font-size: 14px;
}

</style>

<body > 
<div class="grid-containerFundo">
  <div class="cardFundo">
  <h1><center>Dados do usuário</center></h1>
    <div class="grid-container">
      <div class="card">
        <h2>
          Verifique seu email.
        </h2>
      </div>
    </div>
  </div>
</div>

    <footer>
      <center>
      <p>Desenvolvido por Fikiria - 2019</p>
      </center>
    </footer>
</body>
</html>
)=====";
