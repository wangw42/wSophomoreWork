var express = require("express");
var app = express();
var path = require('path');
var fs = require('fs');
var bodyParser = require('body-parser');
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));

var server = require("http").createServer(app);


const Configuration = require("../nodejs-sdk/packages/api/common/configuration.js").Configuration;
Configuration.setConfig("../nodejs-sdk/packages/cli/conf/config.json");


var web3jService = require("../nodejs-sdk/packages/api").Web3jService;
web3 = new web3jService();
var utils = require("../nodejs-sdk/packages/api/common/web3lib/utils");


app.listen(8080, function(){  
  console.log('App listening at port 8080');  
});

app.use(express.static(path.join(__dirname, 'public')));


web3.deploy("../nodejs-sdk/packages/cli/Contracts/SupplyChain.sol","/Users/wangyueqi/nodejs-sdk/packages/cli/Contracts")
.then(function(res){
  //return object res
  console.log('Contract deploying...');
  console.log(res.contractAddress);
  contractAddress = res.contractAddress;
}, err => console.log(err));

//createCompany
app.post('/newCompany', function(req,res){

    var companyName = req.body.companyName;
    var companyType = req.body.companyType;

    //return res.redirect(200, "localhost:8080");
    
    //res.send("rua");
    
    var promise1 = new Promise(function(res,rej){
        res(web3.sendRawTransaction(contractAddress,'newCompany(string,string)',[companyName,companyType]));
    });
    promise1.then(function(value){
      console.log('---------- Creating Company... ----------');
      console.log(value);

      var data = 'Company created! companyName: [' + companyName + '], companyType: [' + companyType + ']';
      return res.send(data);
    })

    
});

//trade
app.post('/trade', function(req,res){
    var tradecompanyFrom = req.body.tradecompanyFrom;
    var tradecompanyTo = req.body.tradecompanyTo;
    var tradeproductName = req.body.tradeproductName;
    var tradeAmount = req.body.tradeAmount;

    var promise2 = new Promise(function(res,rej){
        res(web3.sendRawTransaction(contractAddress,'trade(string,string,string,uint256)',[tradecompanyFrom,tradecompanyTo,tradeproductName,tradeAmount]));
    });
    promise2.then(function(value){
      console.log('---------- Trading... ----------');
      console.log(value);

      var data = 'Success! From: [' + tradecompanyFrom + '], to: [' + tradecompanyTo + '], product: [' + tradeproductName + '], Amount: [' +  tradeAmount + ']';
      return res.send(data);
    })
   
});

//bank
app.post('/bank', function(req,res){
    var bankcompanyName = req.body.bankcompanyName;
    var bankName = req.body.bankName;
    var bankproductName = req.body.bankproductName;
    var bankAmount = req.body.bankAmount;
    var promise3 = new Promise(function(res,rej){
        res(web3.sendRawTransaction(contractAddress,'financeWithBank(string,string,string,uint256)',[bankcompanyName,bankName,bankproductName,bankAmount]));
    });
    promise3.then(function(value){
      console.log('---------- Financing with bank... ----------');
      console.log(value);

      var data = 'Success! From: [' + bankcompanyName + '], Bank: [' + bankName + '], product: [' + bankproductName + '], Amount: [' +  bankAmount + ']';
      return res.send(data);

    })
});

//receipt
app.post('/receipt', function(req,res){
    var receiptcompanyName1 = req.body.receiptcompanyName1;
    var receiptproductName2 = req.body.receiptproductName2;
    var receiptproductName = req.body.receiptproductName;

    var promise4 = new Promise(function(res,rej){
        res(web3.call(contractAddress,'getReceipt(string,string,string)',[receiptcompanyName1,receiptproductName2,receiptproductName]));
    });
    promise4.then(function(value){
      console.log('---------- Getting receipt... ----------');
      console.log(value);

      var result = utils.decodeParams(['bool','string','string','string','string','uint256', 'string'] ,value.result.output);
      console.log(result);
      var data = result;
      return res.send(data);
    })
});

