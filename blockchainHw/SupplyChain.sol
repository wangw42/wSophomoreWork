pragma solidity ^0.4.24;

contract SupplyChain{
    
    enum CreditStatus{Low, High}
    
    struct Company{
        bytes32 companyName;
        bytes32 companyType;
    }
    
    struct Receipt{
        bytes32 fromWho;
        bytes32 to;
        bytes32 product;
        uint256 amount;
        CreditStatus status;
    }
    
    mapping(bytes32 => Company) companyMap;
    mapping(bytes32 => Company) companyNameMap;
    mapping(bytes32 => Company) bankNameMap;
    mapping(bytes32 => mapping(bytes32 => mapping(bytes32 => Receipt))) receiptMap;
    
    address owner;
    
    constructor()public{
        owner = msg.sender;
    }
    
    function stringToBytesVer2(string memory source) public pure returns (bytes32 result) {
        assembly {
            result := mload(add(source, 32))
        }
    }
   
    function newCompany(string memory _companyName, string memory _companyType) public returns (bool, string){
        
        bytes32 _companyName2 = stringToBytesVer2(_companyName);
        bytes32 _companyType2 = stringToBytesVer2(_companyType);
        
        Company storage company = companyMap[_companyName2];
        
        if(_companyType2 != "Bank" &&  _companyType2 != "Company"){
            return (false, "Failed, this company type doesn't exist.");
        }
        
        if(company.companyName != 0x0){
            return (false, "Failed, this company already exist.");
        }
        
        company.companyName = _companyName2;
        company.companyType = _companyType2;
        if(_companyType2 == "Company"){
            companyNameMap[_companyName2] = company;
        } else if(_companyType2 == "Bank"){
            bankNameMap[_companyName2] = company;
        }
        
        return (true, "Succeed created company.");
    }
    
    
    
    function updateReceipt(bytes32 _from, bytes32 _to, bytes32 _product, uint256 _amount, CreditStatus _status) internal returns(bool, string){
        Receipt storage receipt = receiptMap[_from][_to][_product];
        
        receipt.amount += _amount;
        receipt.status = _status;
        
        return (true, "Success update receipt.");
    }
    
    function financeWithBank(string _companyName, string _bankName, string _product, uint256 _amount) public returns(bool, string){
        
        bytes32 _companyName2 = stringToBytesVer2(_companyName);
        bytes32 _bankName2 = stringToBytesVer2(_bankName);
        bytes32 _product2 = stringToBytesVer2(_product);
        
        Company memory company = companyMap[_companyName2];
        
        if(bankNameMap[_bankName2].companyName == 0x0){
            return (false, "Failed, this bank doesn't exist.");
        }
        
        if(company.companyName == 0x0 || company.companyType != "Company"){
            return (false, "Failed, this company doesn't exist or type wrong.");
        }
        
        updateReceipt(company.companyName, _bankName2, _product2, _amount, CreditStatus.High);
        return (true, "Success.");
    }
    
    function trade(string _from, string _to, string _product, uint256 _amount) public returns(bool, string){
        
        bytes32 _from2 = stringToBytesVer2(_from);
        bytes32 _to2 = stringToBytesVer2(_to);
        bytes32 _product2 = stringToBytesVer2(_product);
        
        Company memory company = companyMap[_from2];
        
        if(companyNameMap[_to2].companyName == 0x0){
            return (false, "Failed, this target company doesn't exist.");
        }
        
       
        if(company.companyName == 0x0 ){
            return (false, "Failed, this company doesn't exist or type wrong.");
        }
        
        updateReceipt(company.companyName, _to2, _product2, _amount, CreditStatus.Low);
        return (true, "Success.");
    }
    
    
    function getReceipt(string _from, string _to, string _product) public view returns
        (bool, string, string , string , string , uint256 , string ){
        Receipt memory receipt;
        
        bytes32 _from2 = stringToBytesVer2(_from);
        bytes32 _to2 = stringToBytesVer2(_to);
        bytes32 _product2 = stringToBytesVer2(_product);
        
        if(receiptMap[_from2][_to2][_product2].amount == 0){
            return (false, "Failed, no debt between them, or information wrong.", "0","0","0",0,"Low");
        }
        
        receipt = receiptMap[_from2][_to2][_product2];
        string memory retstatus;
        if(receipt.status == CreditStatus.High)
            retstatus = "High";
        else 
            retstatus = "Low";
        
        
        return (true, "Succeed got receipt.",  _from, _to, _product, receipt.amount, retstatus);
    }
    
    function byte32ToString(bytes32 b) public pure returns (string) {
       
       bytes memory names = new bytes(b.length);
       
       for(uint i = 0; i < b.length; i++) {
           
           names[i] = b[i];
       }
       
       return string(names);
   }
    
}
/*
pragma solidity ^0.4.24;

contract SupplyChain2{
    
    enum CreditStatus{Low, High}
    
    struct Company{
        bytes32 companyName;
        bytes32 companyType;
    }
    
    struct Receipt{
        bytes32 fromWho;
        bytes32 to;
        bytes32 product;
        uint256 amount;
        CreditStatus status;
    }
    
    mapping(address => Company) companyMap;
    mapping(bytes32 => Company) companyNameMap;
    mapping(bytes32 => Company) bankNameMap;
    mapping(bytes32 => mapping(bytes32 => mapping(bytes32 => Receipt))) receiptMap;
    
    address owner;
    
    constructor()public{
        owner = msg.sender;
    }
    
    function stringToBytesVer2(string memory source) public pure returns (bytes32 result) {
        assembly {
            result := mload(add(source, 32))
        }
    }
   
    function newCompany(string memory _companyName, string memory _companyType) public returns (bool, string){
        Company storage company = companyMap[msg.sender];
        bytes32 _companyName2 = stringToBytesVer2(_companyName);
        bytes32 _companyType2 = stringToBytesVer2(_companyType);
        
        if(_companyType2 != "Bank" &&  _companyType2 != "Company"){
            return (false, "Failed, this company type doesn't exist.");
        }
        
        if(company.companyName != 0x0){
            return (false, "Failed, this company already exist.");
        }
        
        company.companyName = _companyName2;
        company.companyType = _companyType2;
        if(_companyType2 == "Company"){
            companyNameMap[_companyName2] = company;
        } else if(_companyType2 == "Bank"){
            bankNameMap[_companyName2] = company;
        }
        
        return (true, "Succeed created company.");
    }
    
    
    
    function updateReceipt(bytes32 _from, bytes32 _to, bytes32 _product, uint _amount, CreditStatus _status) internal returns(bool, string){
        Receipt storage receipt = receiptMap[_from][_to][_product];
        
        receipt.amount += _amount;
        receipt.status = _status;
        
        return (true, "Success update receipt.");
    }
    
    function financeWithBank(string _bankName, string _product, uint _amount) public returns(bool, string){
        Company memory company = companyMap[msg.sender];
        bytes32 _bankName2 = stringToBytesVer2(_bankName);
        bytes32 _product2 = stringToBytesVer2(_product);
        
        if(bankNameMap[_bankName2].companyName == 0x0){
            return (false, "Failed, this bank doesn't exist.");
        }
        
        if(company.companyName == 0x0 || company.companyType != "Company"){
            return (false, "Failed, this company doesn't exist or type wrong.");
        }
        
        updateReceipt(company.companyName, _bankName2, _product2, _amount, CreditStatus.High);
        return (true, "Success.");
    }
    
    function trade(string _to, string _product, uint _amount) public returns(bool, string){
        Company memory company = companyMap[msg.sender];
        bytes32 _to2 = stringToBytesVer2(_to);
        bytes32 _product2 = stringToBytesVer2(_product);
        
        if(companyNameMap[_to2].companyName == 0x0){
            return (false, "Failed, this target company doesn't exist.");
        }
        
       
        if(company.companyName == 0x0 ){
            return (false, "Failed, this company doesn't exist or type wrong.");
        }
        
        updateReceipt(company.companyName, _to2, _product2, _amount, CreditStatus.Low);
        return (true, "Success.");
    }
    
    
    function getReceipt(string _from, string _to, string _product) public view returns
        (bool, string, bytes32 fromwho, bytes32 to, bytes32 product, uint amount, CreditStatus status){
        Receipt memory receipt;
        
        bytes32 _from2 = stringToBytesVer2(_from);
        bytes32 _to2 = stringToBytesVer2(_to);
        bytes32 _product2 = stringToBytesVer2(_product);
        
        if(receiptMap[_from2][_to2][_product2].amount == 0){
            return (false, "Failed, no debt between them, or information wrong.", "0","0","0",0,CreditStatus.Low);
        }
        
        receipt = receiptMap[_from2][_to2][_product2];
        
        
        return (true, "Succeed got receipt.",  receipt.fromWho, receipt.to, receipt.product, receipt.amount, receipt.status);
    }
    
    
}

*/