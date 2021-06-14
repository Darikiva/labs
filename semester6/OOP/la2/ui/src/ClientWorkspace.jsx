import { Component } from "react";
import Greeting from "./Greeting.jsx";
import $ from "jquery"

const ClientWorkspace = props => {
    const listBooks = () => {
        const response = fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'list_books'
                })
            });
        let data = response.json();
        let select = $('#books');
        select.empty();
        $.each(data, function (index, item) {
            select.append('<option name="book" value="' + item.id + '">' + item.name + '</option>');
        });
    }

    const listReqs = () => {
        const response = fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'list_requests',
                    id_user: localStorage.getItem("id_iser")
                })
            });
        let data = response.json();
        let select = $('#reqs');
        select.empty();
        $.each(data, function (index, item) {
            select.append('<option name="req" value="' + item.id_book + '">' + item.id_book + ' ' + item.accepted + '</option>');
        });
    }

    const takeBook = () => {
        let select = $('#books').find(":selected");
        const response = fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'take_book',
                    id_user: localStorage.getItem("id_iser"),
                    id_book: select.val()
                })
            });
        let data = response.json();
        let stat = $('#status');
        if (data.status == false) {
            stat.text(data.message);
        } else {
            localStorage.setItem("current_book", select.val());
            $('#reading_book').text(localStorage.getItem("current_book"));
            stat.text("Success");
        }
    }

    const returnBook = () => {
        fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'return_book',
                    id_user: localStorage.getItem("id_iser"),
                    id_book: localStorage.getItem("current_book")
                })
            });
        localStorage.setItem("current_book", -1);
        $('#reading_book').text("-1");
    }

    const requestBook = () => {
        let select = $('#books').find(":selected");
        fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'request_book',
                    id_user: localStorage.getItem("id_iser"),
                    id_book: select.val()
                })
            });
    }

    const unrequestBook = () => {
        let select = $('#reqs').find(":selected");
        fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'unrequest_book',
                    id_user: localStorage.getItem("id_iser"),
                    id_book: select.val()
                })
            });
    }

    const takeHome = () => {
        let select = $('#reqs').find(":selected");
        const response = fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'take_home',
                    id_user: localStorage.getItem("id_iser"),
                    id_book: select.val()
                })
            });
        let ans = response.json();
        if (ans.status == false) {
        } else {
            localStorage.setItem("current_book", select.val());
            $('#reading_book').text(localStorage.getItem("current_book"));
        }
    }

    const findBook = () => {
        let idbook = $("#input_find").val();
        const response = fetch('http://localhost:8080/lab1/client',
            {
                method: 'POST',
                redirect: 'follow',
                body: JSON.stringify({
                    action: 'find_book',
                    id_book: idbook
                })
            });
        let data = response.json();
        let select = $("#found");
        select.empty();
        $.each(data, function (index, item) {
            select.append('<option name="book" value="' + item.id + '">' + item.name + " " + item.amount + '</option>');
        });
    }

    const changeReadingBook = () => {
        $('#reading_book').text(localStorage.getItem("current_book"));
    }

    // async componentDidMount() {
    //     this.listBooks = this.listBooks.bind(this);
    //     this.listReqs = this.listReqs.bind(this);
    //     this.takeBook = this.takeBook.bind(this);
    //     this.returnBook = this.returnBook.bind(this);
    //     this.requestBook = this.requestBook.bind(this);
    //     this.unrequestBook = this.unrequestBook.bind(this);
    //     this.takeHome = this.takeHome.bind(this);
    //     this.changeReadingBook = this.changeReadingBook.bind(this);
    //     this.findBook = this.findBook.bind(this);

    //     this.listBooks();
    //     const response = await fetch('http://localhost:8080/lab1/client',
    //         {
    //             method: 'POST',
    //             redirect: 'follow',
    //             body: JSON.stringify({
    //                 action: 'get_reading',
    //                 id_user: localStorage.getItem("id_iser")
    //             })
    //         });
    //     let data = await response.json();
    //     if (data.status != false) {
    //         localStorage.setItem("current_book", data.id_book);
    //     } else {
    //         localStorage.setItem("current_book", -1);
    //     }
    //     this.changeReadingBook();
    // }

    return (
        <div width="100%">
            <form autoComplete={"off"}>
                <Greeting />
                <br />
                Client
                <table width="100%" class="grid">
                    <tbody>
                        <tr>
                            <td>
                                <button id="list_books" onClick={listBooks}>List books</button>
                            </td>
                            <td>
                                <button id="list_reqs" onClick={listReqs}>List requests</button>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <select id="books" size="3" width="100%"></select>
                            </td>
                            <td>
                                <select id="reqs" size="3"></select>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <button id="take_book" onClick={takeBook}>Read book here</button>
                                <button id="request_book" onClick={requestBook}>Request book to home</button>
                                <button id="return book" onClick={returnBook}>Return book</button>
                            </td>
                            <td>
                                <button id="unrequest_book" onClick={unrequestBook}>Unrequest book</button>
                                <button id="take_home" onClick={takeHome}>Take book to home</button>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <p id="status"> wooow </p>
                            </td>
                            <td>
                                You're reading a book with id =
                                <p id="reading_book"></p>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <input id="input_find"></input>
                                <button id="find" onClick={findBook}>Find</button>
                            </td>
                            <td>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <select id="found" size="5"></select>
                            </td>
                        </tr>
                    </tbody>
                </table>
            </form>
        </div>
    )
}

export default ClientWorkspace;