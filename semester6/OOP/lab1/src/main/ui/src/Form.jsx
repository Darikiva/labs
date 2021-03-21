import { Component } from 'react';
import $ from "jquery";
import './style.css';
import Cookies from 'universal-cookie';

const cookies = new Cookies();

class Form extends Component {
  constructor(props) {
    super(props);
    this.state = {
      login: '',
      password: ''
    };
    this.onHandleChangeLogin = this.onHandleChangeLogin.bind(this);
    this.onHandleChangePassword = this.onHandleChangePassword.bind(this);
    this.componentDidMount = this.componentDidMount.bind(this);
  }

  componentDidMount() {
    localStorage.setItem("username", '');


    $(document).on("submit", "#loginform", async function (event) {

      cookies.remove("LOGIN");
      cookies.remove("PASSWORD");
      cookies.remove("ROLE", { path: '/lab1' });
      cookies.set("LOGIN", this.state.login, { path: '/lab1' });
      cookies.set("PASSWORD", this.state.password, { path: '/lab1' });
      async function postData(url = '', data = {}) {
        const response = await fetch(url,
          {
            method: 'POST',
            redirect: 'follow',
            body: JSON.stringify(data)
          });
        return await response.json();
      }

      postData('http://localhost:8080/lab1/login', {
        login: this.state.login,
        password: this.state.password
      })
        .then((data) => {
          localStorage.setItem("username", data.name);
          localStorage.setItem("id_iser", data.id);
          if (data.admin) {
            window.location.href = '/l_u=' + this.state.login;
          } else {
            window.location.href = '/c_u=' + this.state.login;
          }
        })
        .catch((error) => {
          alert(error)
        });

      this.setState({
        password: ""
      });
    }.bind(this));
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

          <button type="submit">Submit</button>
        </form>
      </div>
    )
  }
}

export default Form;