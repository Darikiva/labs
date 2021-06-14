package com.library.repository;

import java.util.List;
import java.util.Optional;

import com.library.entity.User;

import org.springframework.data.jpa.repository.JpaRepository;


public interface UserRepository extends JpaRepository<User, Long> {
    Optional<User> findById(long id);

    List<User> findByLogin(String login);

    Optional<User> findByPassword(String password);
}
