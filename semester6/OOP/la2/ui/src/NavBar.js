import React from "react";
import {Link} from "react-router-dom";

const NavBarAuth = props => {
    return (
        <header className="d-flex flex-column p-3 px-md-4 mb-3 bg-white border-bottom shadow-sm">
            <nav className="navbar navbar-light bg-light justify-content-between">
                { ! props.user.username ? <a className="navbar-brand">Racing Bets</a> :
                    <a className="navbar-brand">{ props.user.username }</a> }
                <span className="navbar-text ">
                  <span className="mr-2">
                   <Link to="/"> Main page</Link>
                  </span>
                    <span className="mr-2">
                        { props.loggedIn && <Link to="/" onClick={ props.logOut }> Log Out</Link> }
                        { ( ! props.loggedIn ) && <Link to="/login"> Log In</Link> }
                    </span>
                <Link to="/signup">Register</Link>
                </span>
            </nav>
        </header>
    )
}
export default NavBarAuth;