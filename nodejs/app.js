const express = require("express");
const app = express();
app.get("/",(req,res) =>{
    res.send("hello rorl")
});
const PORT = process.env.PORT || 8000;
app.listen(PORT,() => console.log(`Application listening on port ${PORT}!`));