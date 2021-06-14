import { Component } from 'react';
import $, { get } from "jquery";
import axios from 'axios'
import './style.css';

class Form extends Component {
  constructor(props) {
    super(props);
    this.state = {
      login: '',
      password: '',
      token: '',
    };
    this.onHandleChangeLogin = this.onHandleChangeLogin.bind(this);
    this.onHandleChangePassword = this.onHandleChangePassword.bind(this);
    this.componentDidMount = this.componentDidMount.bind(this);
    this.getToken = this.getToken.bind(this);
    this.submit = this.submit.bind(this);
  }

  getToken(_callback) {
    const qs = require("qs");
    $.post({
      url: 'http://localhost:8080/auth/realms/demo-realm/protocol/openid-connect/token',
      contentType: 'application/x-www-form-urlencoded',
      data: qs.stringify({
        client_id: "springboot-microservice",
        username: this.state.login,
        password: this.state.password,
        grant_type: "password",
        client_secret: "3e9f502b-19eb-4082-9390-457bca0d818f"
      }),
      success: function (res) {
        alert("hey");
        $.get('http://localhost:8000/user', {
          headers: {
            'Authorization': 'bearer ' + res.access_token
          }
        }).then(() => {
          alert("ura");
        })
      },
      error: function () {
        alert("error")
      }
    }).then(res => {
      this.state.token = res.access_token;
    }).catch(error => alert(error));
    _callback();
  }
  
  
  submit() {
    this.getToken(()=>{
      // alert("helo");
      console.log("i'm done");
    })
  }

  componentDidMount() {
    localStorage.setItem("username", '');
  }

  onHandleChangeLogin(e) {
    this.setState({
      login: e.target.value
    });
  }
  onHandleChangePassword(e) {
    this.setState({
      password: e.target.value
    });
  }

  render() {
    return (
      <div>
        <div id="errormsg"></div>
        <form id="loginform">
          <label>Name:
              <input
              type="text"
              name="login"
              onChange={this.onHandleChangeLogin}
              value={this.state.login}
            /><br />
          </label>

          <label>Password:
            <input
              type="password"
              name="password"
              onChange={this.onHandleChangePassword}
              value={this.state.password}
            /><br />
          </label>

          <button type="submit" onClick={this.submit}>Submit</button>
        </form>
      </div>
    )
  }
}

export default Form;