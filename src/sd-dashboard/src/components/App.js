import React, { Component } from 'react';
import axios from 'axios';
import Chart from './Chart';
import Modal from './Modal';
import { hostname, port, timer } from '../../config.json';
import "../style/style.css";

const apiString = `http://${hostname}:${port}/api/v1/`;

export default class App extends Component {
  state = {
    quantity: 0,
    deposits: [],
    changingStatus: false,
    showModal: false
  }

  componentDidMount() {
    this.loadStatus();
    this.loadDeposits();
    setInterval(this.loadStatus, timer * 1000);
    setInterval(this.loadDeposits, timer * 1000);
  }

  loadStatus = async () => {
    try {
      const res = await axios.get(apiString+`status`);
      const { available, quantity } = res.data;
      this.setState(() => ({ 
        available,
        quantity,
        changingStatus: false
      }));
    } catch (err) { console.log(err, res); }
  }

  loadDeposits = async () => {
    try {
      const res = await axios.get(apiString+`deposits`);
      const deposits = res.data;
      this.setState(() => ({ deposits }));
    } catch (err) { console.log(err, res); }
  }

  changeStatus = async () => {
    const body = { available: !this.state.available, quantity: this.state.quantity }
    this.setState(() => ({ changingStatus: true }));
    try {
      await axios.put(apiString+`status`, body);
      this.loadStatus();
    } catch (err) { 
      console.log(err);
      if(err.response.status == 400) this.showModal(); 
    }
  }

  showModal = () => {
    this.setState({ showModal: true });
  };

  hideModal = () => {
    this.setState({ showModal: false });
  };

  renderStatus() {
    return (
      <div className="status-container">
        <div className="card">
            <h4><b>Deposits</b></h4>
            <p>{ this.state.deposits.length }</p>
        </div>
        <div className="card">
            <h4><b>Quantity</b></h4>
            <p>{ this.state.quantity }</p>
        </div>
        <div className={`card ${ this.state.available ? 'success' : 'alert' }`}>
            <h4><b>Status</b></h4>
            <p>{ this.state.available ? "enabled" : "disabled" }</p>
        </div>
      </div>
    );
  }

  renderCharts() {
    const res = this.state.deposits.map(x => ({
      ...x,
      deposits: x.deposits.length
      })
    );
  
    const res2 = this.state.deposits.map(x => ({
      date: x.date,
      quantity: x.deposits.reduce((r, i) => r + i, 0)
    }));
    
    return (
      <div className="charts-container">
       <Chart data={res} title={'Deposits per day'} Xkey={'date'} Ykey={'deposits'} />
       <Chart data={res2} title={'Quantity per day'} Xkey={'date'} Ykey={'quantity'} />
       <button type="button" 
        onClick={this.changeStatus}
        disabled={this.state.changingStatus}
        className={`btn-block ${ this.state.available ? 'alert' : 'success' }`}>
          { this.state.available ? "Disable" : "Enable" }
        </button>
      </div>
    );
  }

  render() {
    return (
      <div>
        <header>
          <h1>Dumpster Dashboard</h1>
        </header>
        <div className="container">
          { this.renderCharts() }
          { this.renderStatus() }
          <Modal show={this.state.showModal} handleClose={this.hideModal}>
            <div className="modal-header">
              <span>Message Box</span>
            </div>
            <div className="modal-content">
              <p>The Dumpster is full!</p>
            </div>
          </Modal>
        </div>
      </div>
    );
  }
}

