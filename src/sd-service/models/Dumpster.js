'use strict'
const fs = require('fs');
const maxCapacity = 100;

class Dumpster {
   constructor(capacity) {
      this.capacity = capacity;
      this._init();
   }
   
   _init() {
      const { deposits, status } = JSON.parse(fs.readFileSync('dumpster.json'));
      this.deposits = deposits; 
      this.status = status;
   }

   _saveJson() {
      const data = JSON.stringify({status: this.status, deposits: this.deposits});
      fs.writeFileSync('dumpster.json', data);
   }
   
   getCapacity() {
       return this.capacity;
   }

   getDeposits() {
       return this.deposits;
   }
   
   saveDeposit(deposit) {
      this.status.quantity += deposit.quantity;
      this.deposits.push(deposit);
      this._saveJson();
   }

   setStatus(available, quantity) {
      this.status.available = available;
      this.status.quantity = quantity;
      this._saveJson();
   }

   getStatus() {
     return this.status;
   }

   isFull() {
     return this.status.quantity >= this.capacity;
   }
}


module.exports = new Dumpster(maxCapacity);
